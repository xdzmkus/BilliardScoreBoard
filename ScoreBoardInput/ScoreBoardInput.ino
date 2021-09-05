/** Button map

           SLEEP
 |-----------------------------|
 |         DOWN                |
 |----------------------|      |
 |  UP      AS     AL1  |      | POWER   MODE
 |------|-------|-------|      |-------|-------|
 ===============================================
 1      2       3       4      5       6       7
 ===============================================
        |       |--------------|       |
        |             C/F              |
        |------------------------------|
                      AL2

 * red          - SLEEP
 * black        - POWER
 * pink         - AS
 * blue         - MODE
 * brown        - C/F
 * green        - AL1
 * yellow       - AL2
 * white/red    - DOWN
 * white/black  - UP
 */


/* Atmega168 mapping */
#define BUTTON_PIN1 8 // PB0
#define BUTTON_PIN2 7 // PD7
#define BUTTON_PIN3 6 // PD6
#define BUTTON_PIN4 5 // PD5
#define BUTTON_PIN5 4 // PD4
#define BUTTON_PIN6 3 // PD3
#define BUTTON_PIN7 2 // PD2

#define SNOOKER_BUTTON_PIN  10  // snooker / frames only
#define TIMER_BUTTON_PIN    11	// time limit / infinity
#define RESET_BUTTON_PIN    12	// reset / start

#include "ScoreBoardConnection.h"

volatile bool connACK = true;

BOARD_STATE lastBoardState = { 0 };

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, LOW);   // Turn off

    pinMode(SNOOKER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(TIMER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

    pinMode(BUTTON_PIN1, INPUT_PULLUP);
    pinMode(BUTTON_PIN2, INPUT_PULLUP);
    pinMode(BUTTON_PIN3, INPUT_PULLUP);
    pinMode(BUTTON_PIN4, INPUT_PULLUP);
    pinMode(BUTTON_PIN5, INPUT_PULLUP);
    pinMode(BUTTON_PIN6, INPUT_PULLUP);
    pinMode(BUTTON_PIN7, INPUT_PULLUP);

    Serial.begin(SERIAL_BAUD);
}

void loop()
{
     buttonProcess();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
    String ack = Serial.readStringUntil('\n');
    ack.trim();

    if (ack.equals(BOARD_MESSAGE_ACK))
    {
        Serial.flush();
        connACK = true;
    }
    else if (ack.equals(BOARD_MESSAGE_INIT))
    {
        Serial.flush();
        sendCurrentState();
        connACK = false;
    }
}

void sendCurrentState()
{
    Serial.println(BOARD_MESSAGE + lastBoardState.overallState);
}

void buttonProcess()
{
    if (!connACK) return;

    BOARD_STATE boardState = { CRC };

    boardState.btnState.reset = isResetState();
    boardState.btnState.timer = isTimerState();
    boardState.btnState.snooker = isSnookerState();
    boardState.btnState.btnBlue = isBtnPressed_MODE();
    boardState.btnState.btnBlack = isBtnPressed_POWER();
    boardState.btnState.btnPink = isBtnPressed_AS();
    boardState.btnState.btnBrown = isBtnPressed_CF();
    boardState.btnState.btnRed = isBtnPressed_SLEEP();
    boardState.btnState.btnGreen = isBtnPressed_AL1();
    boardState.btnState.btnYellow = isBtnPressed_AL2();
    boardState.btnState.btnWhiteBlack = isBtnPressed_UP();
    boardState.btnState.btnWhiteRed = isBtnPressed_DOWN();

    if (lastBoardState.overallState != boardState.overallState)
    {
        lastBoardState = boardState;
        sendCurrentState();
        connACK = false;
    }
}

boolean isSnookerState()
{
    return digitalRead(SNOOKER_BUTTON_PIN);
}

boolean isTimerState()
{
    return digitalRead(TIMER_BUTTON_PIN);
}

boolean isResetState()
{
    return digitalRead(RESET_BUTTON_PIN);
}

boolean isBtnPressed_MODE()
{
    // PIN7 - PIN6 connected

    // PIND = 111100xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN7, OUTPUT);
    digitalWrite(BUTTON_PIN7, LOW);

    if (((PIND & B11111100) == B11110000) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN7, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_POWER()
{
    // PIN6 - PIN5 connected

    // PIND = 111001xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN6, OUTPUT);
    digitalWrite(BUTTON_PIN6, LOW);

    if (((PIND & B11111100) == B11100100) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN6, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_AL2()
{
    // PIN6 - PIN2 connected

    // PIND = 011101xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN6, OUTPUT);
    digitalWrite(BUTTON_PIN6, LOW);

    if (((PIND & B11111100) == B01110100) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN6, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_CF()
{
    // PIN5 - PIN3 connected

    // PIND = 101011xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN5, OUTPUT);
    digitalWrite(BUTTON_PIN5, LOW);

    if (((PIND & B11111100) == B10101100) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN5, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_SLEEP()
{
    // PIN5 - PIN1 connected

    // PIND = 111011xx
    // PINB = xxxxxxx0

    boolean pressed = false;

    pinMode(BUTTON_PIN5, OUTPUT);
    digitalWrite(BUTTON_PIN5, LOW);

    if (((PIND & B11111100) == B11101100) && (bitRead(PINB, 0) == 0))
        pressed = true;

    pinMode(BUTTON_PIN5, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_AL1()
{
    // PIN4 - PIN3 connected

    // PIND = 100111xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN4, OUTPUT);
    digitalWrite(BUTTON_PIN4, LOW);

    if (((PIND & B11111100) == B10011100) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN4, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_DOWN()
{
    // PIN4 - PIN1 connected

    // PIND = 110111xx
    // PINB = xxxxxxx0

    boolean pressed = false;

    pinMode(BUTTON_PIN4, OUTPUT);
    digitalWrite(BUTTON_PIN4, LOW);

    if (((PIND & B11111100) == B11011100) && (bitRead(PINB, 0) == 0))
        pressed = true;

    pinMode(BUTTON_PIN4, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_AS()
{
    // PIN3 - PIN2 connected

    // PIND = 001111xx
    // PINB = xxxxxxx1

    boolean pressed = false;

    pinMode(BUTTON_PIN3, OUTPUT);
    digitalWrite(BUTTON_PIN3, LOW);

    if (((PIND & B11111100) == B00111100) && (bitRead(PINB, 0) == 1))
        pressed = true;

    pinMode(BUTTON_PIN3, INPUT_PULLUP);
    return pressed;
}

boolean isBtnPressed_UP()
{
    // PIN2 - PIN1 connected

    // PIND = 011111xx
    // PINB = xxxxxxx0

    boolean pressed = false;

    pinMode(BUTTON_PIN2, OUTPUT);
    digitalWrite(BUTTON_PIN2, LOW);

    if (((PIND & B11111100) == B01111100) && (bitRead(PINB, 0) == 0))
        pressed = true;

    pinMode(BUTTON_PIN2, INPUT_PULLUP);
    return pressed;
}
