#define BUZZER_PIN 12   // buzzer pin 
#define FREQUENCY_OK 3000  // KHz for beep
#define FREQUENCY_FAIL 4000  // KHz for beep

#define BTN_PIN 13      // touch button
#include <ArduinoDebounceButton.h>
ArduinoDebounceButton touchBtn(BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_RESET A6 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define	RED     0xF800
#define	BLACK   0x0000
#define PINK    0xF81F
#define	BLUE    0x001F
#define BROWN   0x79E0
#define	GREEN   0x07E0
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#include "ScoreBoardConnection.h"
#include "ScoreBoard.h"
ScoreBoard Board;

String receivedState = "";      // received state from button's part
volatile bool vf_BoardStateChanged = false; // is new board's state received?

#include <TimerOne.h>
volatile bool vf_TimerEvent = false;

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS3231 rtc;

bool showSeconds = true;

void setupTFT()
{
    tft.reset();

    uint16_t identifier = tft.readID();

    tft.begin(identifier);

    tft.setRotation(1);
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

    setupTFT();

    Serial.begin(SERIAL_BAUD);
    Serial.println(BOARD_MESSAGE_INIT);

    Timer1.initialize();
    Timer1.setPeriod(1000000UL);
    Timer1.attachInterrupt(isr_processTimer);

    startTicker();
    delay(1500);
}


void isr_processTimer()
{
    vf_TimerEvent = true;
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
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
        processClick();
        break;
    case BUTTON_EVENT::DoubleClicked:
        processDoubleClick();
        break;
    case BUTTON_EVENT::LongPressed:
        processLongClick();
        break;
    default:
        break;
    }
}

void processClick()
{
    if (Board.getResetMode())
    {
        // in reset mode show next timer limit
        if (Board.getTimerMode())
        {
            Board.setTimerNextMaxValue();
            lcd_PrintTimerValue(Board.getTimerMaxValue(), false);
        }
        return;
    }

    // if timer is ON then extend time in game mode
    if (Board.getTimerMode())
    {
        extendTimer();
    }
}

void processDoubleClick()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer
    if (Board.isShotStarted())
        stopTimer();

    // swap started shot in Frames mode
    if (!Board.getSnookerMode())
    {
        Board.swapStartedPlayer();
        tone(BUZZER_PIN, FREQUENCY_OK, 100);
        lcd_DrawScoreBoard();
    }
    // swap focus in Snooker mode
    else
    {
        Board.swapActivePlayer();
        lcd_DrawScoreBoard();
    }
}

void processLongClick()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }
}


void updateBoardState()
{
    if (receivedState.startsWith(BOARD_MESSAGE))
    {
        BOARD_STATE recivedBoardState = { receivedState.substring(receivedState.indexOf(':') + 1).toInt() };

        if (recivedBoardState.btnState.crc != CRC) return;  // not valid state

        processBoardState(recivedBoardState.btnState);
    }

    // clear the string:
    receivedState = "";

    // send response
    Serial.println(BOARD_MESSAGE_ACK);
}

void processBoardState(BOARD_STATE::BOARD_BUTTONS btnState)
{
    // check if modes are changed:
    bool stateChanged = false;

    if (Board.getResetMode() != btnState.reset)
    {
        Board.setResetMode(btnState.reset);
        stateChanged = true;
    }

    if (Board.getTimerMode() != btnState.timer)
    {
        Board.setTimerMode(btnState.timer);
        stateChanged = true;
    }
    
    if (Board.getSnookerMode() != btnState.snooker)
    {
        Board.setSnookerMode(btnState.snooker);
        stateChanged = true;
    }

    if (stateChanged) processModes();

    // check if buttons clicked:
    if (btnState.btnRed) processBtnRed();
    if (btnState.btnBlack) processBtnBlack();
    if (btnState.btnPink) processBtnPink();
    if (btnState.btnBlue) processBtnBlue();
    if (btnState.btnBrown) processBtnBrown();
    if (btnState.btnGreen) processBtnGreen();
    if (btnState.btnYellow) processBtnYellow();
    if (btnState.btnWhiteRed) processBtnWhiteRed();
    if (btnState.btnWhiteBlack) processBtnWhiteBlack();
}

void processModes()
{
    // stop shot's timer in case of mode changes
    if (Board.isShotStarted())
    {
        stopTimer();
    }

    stopTicker();

    if (Board.getResetMode())
    {        
        Board.reset();

        // if timer is ON then show timer limits
        if (Board.getTimerMode())
        {
            lcd_PrintTimerValue(Board.getTimerMaxValue(), true);
        }
        // if timer is OFF then show current time
        else
        {
            startTicker();
        }

        return;
    }

    // reset scores in Frames mode
    if (!Board.getSnookerMode())
    {
        Board.resetScores();
    }

    lcd_DrawScoreBoard();
}

void processBtnRed()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::red);

        lcd_DrawScoreBoard();
    }
    // focus RED player and start timer in Frames mode
    else
    {
        Board.setActivePlayer(BoardPlayers::PLAYER2);

        lcd_DrawScoreBoard();

        if (Board.getTimerMode())
            startTimer();
    }
}

void processBtnBlack()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::black);

        lcd_DrawScoreBoard();
    }
    // focus BLACK player and start timer in Frames mode
    else
    {
        Board.setActivePlayer(BoardPlayers::PLAYER1);

        lcd_DrawScoreBoard();

        if (Board.getTimerMode())
            startTimer();
    }
}

void processBtnPink()
{
    if (Board.getResetMode())
    {
        if (!Board.getTimerMode())
        {
            // add 1 hour
            DateTime future(rtc.now() + TimeSpan(0, 1, 0, 0));
            rtc.adjust(future);
        }
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::pink);

        lcd_DrawScoreBoard();
    }
}

void processBtnBlue()
{
    if (Board.getResetMode())
    {
        if (!Board.getTimerMode())
        {
            // add 1 minute
            DateTime now = rtc.now();
            DateTime future(now + TimeSpan(0, 0, 1, 0));
            if (future.hour() != now.hour())
                future = future - TimeSpan(0, 1, 0, 0);
            rtc.adjust(future);
        }
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::blue);

        lcd_DrawScoreBoard();
    }
}

void processBtnBrown()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::brown);

        lcd_DrawScoreBoard();
    }
}

void processBtnGreen()
{
    if (Board.getResetMode())
    {
        if (!Board.getTimerMode())
        {
            // add 3 hour
            DateTime future(rtc.now() + TimeSpan(0, 3, 0, 0));
            rtc.adjust(future);
        }
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::green);

        lcd_DrawScoreBoard();
    }
}

void processBtnYellow()
{
    if (Board.getResetMode())
    {
        if (!Board.getTimerMode())
        {
            // add 5 minutes
            DateTime now = rtc.now();
            DateTime future(now + TimeSpan(0, 0, 5, 0));
            if (future.hour() != now.hour())
                future = future - TimeSpan(0, 1, 0, 0);
            rtc.adjust(future);
        }
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
    {
        stopTimer();
        lcd_DrawScoreBoard();
    }

    // add score value in Snooker mode
    if (Board.getSnookerMode())
    {
        Board.ballInPocket(SnookerBalls::yellow);

        lcd_DrawScoreBoard();
    }
}

void processBtnWhiteRed()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
        stopTimer();

    // focus RED player
    Board.setActivePlayer(BoardPlayers::PLAYER2);

    // start timer in Snooker mode
    if (Board.getSnookerMode())
    {
        lcd_DrawScoreBoard();

        if (Board.getTimerMode())
            startTimer();
    }
    // add won frame in Frames mode
    else
    {
        Board.addWonFrame(BoardPlayers::PLAYER2);
        Board.swapStartedPlayer();
        tone(BUZZER_PIN, FREQUENCY_OK, 100);
        lcd_DrawScoreBoard();
    }
}

void processBtnWhiteBlack()
{
    if (Board.getResetMode())
    {
        return;
    }

    // stop shot's timer in case of state changes
    if (Board.isShotStarted())
        stopTimer();

    // focus BLACK player
    Board.setActivePlayer(BoardPlayers::PLAYER1);

    // start timer in Snooker mode
    if (Board.getSnookerMode())
    {
        lcd_DrawScoreBoard();

        if (Board.getTimerMode())
            startTimer();
    }
    // add won frame in Frames mode
    else
    {
        Board.addWonFrame(BoardPlayers::PLAYER1);
        Board.swapStartedPlayer();
        tone(BUZZER_PIN, FREQUENCY_OK, 100);
        lcd_DrawScoreBoard();
    }
}


void updateTimer()
{
    if (Board.getShotRemainder() == 0)
    {
        stopTimer();
        lcd_DrawScoreBoard();
        tone(BUZZER_PIN, FREQUENCY_FAIL, 300);
        return;
    }

    Board.tickShot();

    uint8_t timerValue = Board.getShotRemainder();

    lcd_PrintTimerValue(timerValue, false);

    if (timerValue == 0)
    {
        tone(BUZZER_PIN, FREQUENCY_OK, 1000);  // last chanse - long beep
    }
    else if (timerValue >= 3 && timerValue <= 5)
    {
        tone(BUZZER_PIN, FREQUENCY_OK, 400);  // last 2 seconds without beep
    }
}

void stopTimer()
{
    Timer1.stop();

    Board.stopShot();
}

void startTimer()
{
    Timer1.restart();

    Board.startShot();

    lcd_PrintTimerValue(Board.getShotRemainder(), true);

    vf_TimerEvent = false;  // clear an undesired interrupt

    tone(BUZZER_PIN, FREQUENCY_OK, 200);
}

void extendTimer()
{
    tone(BUZZER_PIN, FREQUENCY_OK, 200);

    if (!Board.extendShot()) tone(BUZZER_PIN, FREQUENCY_FAIL, 200);
}


void startTicker()
{
    Timer1.restart();

    showSeconds = true;

    DateTime displayedTime = rtc.now();

    tft.fillScreen(WHITE);

    lcd_PrintTimeHours(displayedTime.hour(), false);
    lcd_PrintTimeSeconds();
    lcd_PrintTimeMinutes(displayedTime.minute(), false);

    vf_TimerEvent = false;  // clear an undesired interrupt
}

void stopTicker()
{
    Timer1.stop();
}

void updateTicker()
{
    showSeconds = !showSeconds;
    lcd_PrintTimeSeconds();

    DateTime now = rtc.now();

    lcd_PrintTimeMinutes(now.minute(), true);
    lcd_PrintTimeHours(now.hour(), true);
}


void lcd_PrintTimeSeconds()
{
    int16_t  x, y;
    uint16_t w, h;

    char colon[] = ":";

    if(showSeconds)
    {
        tft.setTextColor(BLACK);
    }
    else
    {
        tft.setTextColor(WHITE);
    }
    tft.setTextSize(11);
    tft.getTextBounds(colon, 0, 0, &x, &y, &w, &h);
    tft.setCursor(20 + (300 - w)/2, 120 - h/2);
    tft.print(colon);
}

void lcd_PrintTimeHours(uint8_t hours, bool clearPrev)
{
    static uint8_t prevValue = 0;

    int16_t  x, y;
    uint16_t w, h;

    tft.setTextSize(11);

    if (clearPrev)
    {
        if (prevValue == hours) return;

        tft.setTextColor(WHITE);

        String hrs;
        if (prevValue <= 9) hrs += "0";
        hrs += prevValue;

        tft.getTextBounds(hrs, 0, 0, &x, &y, &w, &h);
        tft.setCursor(25 + (140 - w)/2, 120 - h/2);
        tft.print(hrs);
    }

    prevValue = hours;

    tft.setTextColor(BLACK);

    String hrs;
    if (prevValue <= 9) hrs += "0";
    hrs += prevValue;

    tft.getTextBounds(hrs, 0, 0, &x, &y, &w, &h);
    tft.setCursor(25 + (140 - w)/2, 120 - h/2);
    tft.print(hrs);
}

void lcd_PrintTimeMinutes(uint8_t minutes, bool clearPrev)
{
    static uint8_t prevValue = 0;

    int16_t  x, y;
    uint16_t w, h;

    tft.setTextSize(11);

    if (clearPrev)
    {
        if (prevValue == minutes) return;
        
        tft.setTextColor(WHITE);

        String mins;
        if (prevValue <= 9) mins += "0";
        mins += prevValue;

        tft.getTextBounds(mins, 0, 0, &x, &y, &w, &h);
        tft.setCursor(175 + (140 - w)/2, 120 - h/2);
        tft.print(mins);
    }

    prevValue = minutes;

    tft.setTextColor(BLACK);

    String mins;
    if (prevValue <= 9) mins += "0";
    mins += prevValue;

    tft.getTextBounds(mins, 0, 0, &x, &y, &w, &h);
    tft.setCursor(175 + (140 - w)/2, 120 - h/2);
    tft.print(mins);
}

void lcd_setCursorForCenterValue(uint8_t value)
{
    if (value <= 9)
    {
        tft.setTextSize(25);
        tft.setCursor(110, 40);
    }
    else if (value <= 19)
    {
        tft.setTextSize(22);
        tft.setCursor(50, 45);
    }
    else if(value <= 99)
    {
        tft.setTextSize(20);
        tft.setCursor(60, 50);
    }
    else
    {
        tft.setTextSize(16);
        tft.setCursor(25, 55);
    }
}

void lcd_PrintTimerValue(uint8_t value, bool clearScreen)
{
    static uint8_t prevValue = 0;

    if (clearScreen)
    {
        tft.fillScreen(BLACK);
    }
    else
    {
        lcd_setCursorForCenterValue(prevValue);
        tft.setTextColor(BLACK);
        tft.print(prevValue);
    }

    lcd_setCursorForCenterValue(value);

    if (value <= 5)
    {
        tft.setTextColor(RED);
    }
    else
    {
        tft.setTextColor(GREEN);
    }

    tft.print(value);

    prevValue = value;
}

void lcd_DrawScoreBoard()
{
    int16_t  x, y;
    uint16_t w, h;

    tft.fillRect(0, 0, 170, 240, BLACK);
    tft.fillRect(170, 0, 150, 240, RED);

    // draw rectangle for player in focus
    if (Board.whoIsActive() == BoardPlayers::PLAYER1)
    {
        tft.drawRect(20, 0, 150, 240, WHITE);
        tft.drawRect(23, 3, 144, 234, WHITE);
        tft.drawRect(25, 5, 140, 230, WHITE);
    }
    else
    {
        tft.drawRect(170, 0, 150, 240, WHITE);
        tft.drawRect(173, 3, 144, 234, WHITE);
        tft.drawRect(175, 5, 140, 230, WHITE);
    }

    // draw circle whom is started in 'Frame' mode
    if (!Board.getSnookerMode())
    {
        // draw rectangle for starting player
        if (Board.whoIsStarted() == BoardPlayers::PLAYER1)
        {
            tft.fillCircle(95, 210, 15, WHITE);
        }
        else
        {
            tft.fillCircle(245, 210, 15, WHITE);
        }
    }

    // calculate text size
    uint8_t max_score = Board.getSnookerMode() ? Board.getHighestScore() : Board.getHighestFrames();
    
    if (max_score < 10)
    {
        tft.setTextSize(16);
    }
    else if (max_score >= 100)
    {
        tft.setTextSize(7);
    }
    else
    {
        tft.setTextSize(11);
    }

    // draw scores
    tft.setTextColor(WHITE);

    String player_score;
    
    player_score = Board.getSnookerMode() ? Board.getPlayerScore(BoardPlayers::PLAYER1) : Board.getPlayerFrames(BoardPlayers::PLAYER1);

    tft.getTextBounds(player_score, 0, 0, &x, &y, &w, &h);
    tft.setCursor(25 + (150 - w) / 2, 120 - h / 2);
    tft.print(player_score);

    player_score = Board.getSnookerMode() ? Board.getPlayerScore(BoardPlayers::PLAYER2) : Board.getPlayerFrames(BoardPlayers::PLAYER2);

    tft.getTextBounds(player_score, 0, 0, &x, &y, &w, &h);
    tft.setCursor(175 + (150 - w) / 2, 120 - h / 2);
    tft.print(player_score);

    // draw extensions status
    if (Board.getTimerMode() && (Board.getPlayerExtensionAvailable(BoardPlayers::PLAYER1) || Board.getPlayerExtensionAvailable(BoardPlayers::PLAYER2)))
    {
        tft.setTextSize(2);
        tft.setTextColor(GREEN);

        player_score = "extension";

        tft.getTextBounds(player_score, 0, 0, &x, &y, &w, &h);

        if (Board.getPlayerExtensionAvailable(BoardPlayers::PLAYER1))
        {
            tft.setCursor(20 + (150 - w) / 2, 10);
            tft.print(player_score);
        }
        if (Board.getPlayerExtensionAvailable(BoardPlayers::PLAYER2))
        {
            tft.setCursor(170 + (150 - w) / 2, 10);
            tft.print(player_score);
        }
    }
}


void loop(void)
{
    touchBtn.check();

    if (vf_BoardStateChanged)
    {
        vf_BoardStateChanged = false;
        updateBoardState();
    }

    touchBtn.check();

    if (vf_TimerEvent)
    {
        vf_TimerEvent = false;

        if (Board.getTimerMode() && !Board.getResetMode())
            updateTimer();
        else if (!Board.getTimerMode() && Board.getResetMode())
            updateTicker();
    }

    touchBtn.check();
}
