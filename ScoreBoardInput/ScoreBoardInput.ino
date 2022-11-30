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

#include "CROSS_BTN.h"

/* Atmega168 mapping */
#define BUTTON_PIN1 8 // PB0
#define BUTTON_PIN2 7 // PD7
#define BUTTON_PIN3 6 // PD6
#define BUTTON_PIN4 5 // PD5
#define BUTTON_PIN5 4 // PD4
#define BUTTON_PIN6 3 // PD3
#define BUTTON_PIN7 2 // PD2

SLEEP_BTN   red_btn(BUTTON_PIN5);
POWER_BTN   black_btn(BUTTON_PIN6);
AS_BTN      pink_btn(BUTTON_PIN3);
MODE_BTN    blue_btn(BUTTON_PIN7);
CF_BTN      brown_btn(BUTTON_PIN5);
AL1_BTN     green_btn(BUTTON_PIN4);
AL2_BTN     yellow_btn(BUTTON_PIN6);
DOWN_BTN    whiteRed_btn(BUTTON_PIN4);
UP_BTN      whiteBlack_btn(BUTTON_PIN2);

#define GAME_BUTTON_PIN     10  // snooker / pool 
#define CONFIG_BUTTON_PIN   11	// config / normal
#define RESET_BUTTON_PIN    12	// reset / start

ArduinoDebounceButton game_btn(GAME_BUTTON_PIN, BUTTON_CONNECTED::GND, BUTTON_NORMAL::OPEN);
ArduinoDebounceButton config_btn(CONFIG_BUTTON_PIN, BUTTON_CONNECTED::GND, BUTTON_NORMAL::OPEN);
ArduinoDebounceButton reset_btn(RESET_BUTTON_PIN, BUTTON_CONNECTED::GND, BUTTON_NORMAL::OPEN);

#include "ScoreBoardConnection.h"

volatile bool connACK = true;

BOARD_STATE lastBoardState = { 0 };

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, LOW);   // Turn off

    pinMode(BUTTON_PIN1, INPUT_PULLUP);
    pinMode(BUTTON_PIN2, INPUT_PULLUP);
    pinMode(BUTTON_PIN3, INPUT_PULLUP);
    pinMode(BUTTON_PIN4, INPUT_PULLUP);
    pinMode(BUTTON_PIN5, INPUT_PULLUP);
    pinMode(BUTTON_PIN6, INPUT_PULLUP);
    pinMode(BUTTON_PIN7, INPUT_PULLUP);

    game_btn.initPin();
    config_btn.initPin();
    reset_btn.initPin();

    Serial.begin(SERIAL_BAUD);

    waitUntilDebounced();
}

void waitUntilDebounced()
{
    reset_btn.check();
    config_btn.check();
    game_btn.check();
    blue_btn.check();
    black_btn.check();
    pink_btn.check();
    brown_btn.check();
    red_btn.check();
    green_btn.check();
    yellow_btn.check();
    whiteBlack_btn.check();
    whiteRed_btn.check();

    delay(CROSS_BTN::delayDebounce + 1);
}

void loop()
{
    if (!connACK) return;

    BOARD_STATE boardState = { CRC };

    boardState.btnState.reset = reset_btn.check();
    boardState.btnState.config = config_btn.check();
    boardState.btnState.game = game_btn.check();
    boardState.btnState.btnBlue = blue_btn.check();
    boardState.btnState.btnBlack = black_btn.check();
    boardState.btnState.btnPink = pink_btn.check();
    boardState.btnState.btnBrown = brown_btn.check();
    boardState.btnState.btnRed = red_btn.check();
    boardState.btnState.btnGreen = green_btn.check();
    boardState.btnState.btnYellow = yellow_btn.check();
    boardState.btnState.btnWhiteBlack = whiteBlack_btn.check();
    boardState.btnState.btnWhiteRed = whiteRed_btn.check();

    if (lastBoardState.overallState != boardState.overallState)
    {
        lastBoardState = boardState;
        sendCurrentState();
        connACK = false;
    }
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

