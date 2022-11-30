#define BUZZER_PIN 12       // buzzer pin 
#define FREQUENCY_OK 1000   // KHz for beep
#define FREQUENCY_FAIL 3000 // KHz for beep

#include <ArduinoDebounceButton.h>
#define BTN_PIN 13  // touch button
ArduinoDebounceButton touchBtn(BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <RTClib.h>
RTC_DS3231 rtc;
DateTime now;

#include "ScoreBoard.h"
ScoreBoard Board;

#include "ScoreBoardConnection.h"
bool boardInited = false;
String receivedState = "";      // received state from button's part
volatile bool vf_BoardStateChanged = false; // is new board's state received?

#include <TimerOne.h>
volatile bool vf_TimerEvent = false;

void isr_processTimer()
{
    vf_TimerEvent = true;
}

void beep(bool OK)
{
    OK ? tone(BUZZER_PIN, FREQUENCY_OK, 100) : tone(BUZZER_PIN, FREQUENCY_FAIL, 500);
}

/*
 *  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
 *  routine is run between each time loop() runs, so using delay inside loop can
 *  delay response. Multiple bytes of data may be available.
 */
void serialEvent()
{
    while (Serial.available())
    {
        char inChar = static_cast<char>(Serial.read());
        receivedState += inChar;
        // if the incoming character is a newline, set a flag so the main loop can do something about it:
        if (inChar == '\n')
        {
            receivedState.trim();
            vf_BoardStateChanged = true;
            return;
        }
    }
}

void handleButtonEvent(const DebounceButton* button, BUTTON_EVENT eventType)
{
    switch (eventType)
    {
    case BUTTON_EVENT::Clicked:
        beep(Board.clickMasterBtn());
        break;
    case BUTTON_EVENT::DoubleClicked:
        beep(Board.clickTwiceMasterBtn());
        break;
    case BUTTON_EVENT::LongPressed:
        tone(BUZZER_PIN, FREQUENCY_OK, 300);
        break;
    default:
        break;
    }
}

void updateBoardState(BOARD_STATE::BOARD_BUTTONS btnState, bool masterBtnState)
{
    // update switches:
    Board.update(btnState.reset, btnState.config, btnState.game);

    // check if buttons clicked:
    if (btnState.btnRed)        beep(Board.pressedBtnRed(masterBtnState));
    if (btnState.btnBlack)      beep(Board.pressedBtnBlack(masterBtnState));
    if (btnState.btnPink)       beep(Board.pressedBtnPink(masterBtnState));
    if (btnState.btnBlue)       beep(Board.pressedBtnBlue(masterBtnState));
    if (btnState.btnBrown)      beep(Board.pressedBtnBrown(masterBtnState));
    if (btnState.btnGreen)      beep(Board.pressedBtnGreen(masterBtnState));
    if (btnState.btnYellow)     beep(Board.pressedBtnYellow(masterBtnState));
    if (btnState.btnWhiteRed)   beep(Board.pressedBtnWhiteRed(masterBtnState));
    if (btnState.btnWhiteBlack) beep(Board.pressedBtnWhiteBlack(masterBtnState));

    DateTime newNow = Board.getTime();
    if (now != newNow)
    {
        now = newNow;
        rtc.adjust(newNow);
    }
}

void processBoardState()
{
    if (receivedState.startsWith(BOARD_MESSAGE))
    {
        BOARD_STATE recivedBoardState = { static_cast<uint16_t>(receivedState.substring(receivedState.indexOf(':') + 1).toInt()) };

        if (recivedBoardState.btnState.crc != CRC)
        {
            boardInited = false;
        }
        else
        {
            updateBoardState(recivedBoardState.btnState, touchBtn.check());

            // send response
            Serial.println(BOARD_MESSAGE_ACK);

            boardInited = true;
        }
    }
    else
    {
        boardInited = false;
    }
    // clear the string
    receivedState = "";
}

void setup(void)
{
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, LOW);   // Turn off

    touchBtn.initPin();
    touchBtn.setEventHandler(handleButtonEvent);

    pinMode(BUZZER_PIN, OUTPUT);
    tone(BUZZER_PIN, FREQUENCY_OK, 500);

    rtc.begin();

    Board.begin();

    Timer1.initialize();
    Timer1.setPeriod(1000000UL);
    Timer1.attachInterrupt(isr_processTimer);
    Timer1.start();

    Serial.begin(SERIAL_BAUD);

    delay(2000);
}

void loop(void)
{
    touchBtn.check();

    if (vf_BoardStateChanged)
    {
        vf_BoardStateChanged = false;
        processBoardState();
    }

    if (vf_TimerEvent)
    {
        vf_TimerEvent = false;

        if (boardInited == false)
        {
            // send init request
            Serial.println(BOARD_MESSAGE_INIT);
        }

        now = rtc.now();

        Board.setTime(now);
    }
}
