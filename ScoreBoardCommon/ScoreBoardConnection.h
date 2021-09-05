#pragma once

const unsigned long SERIAL_BAUD = 115200UL;

union BOARD_STATE
{
    uint16_t overallState;
    struct BOARD_BUTTONS
    {
        uint8_t crc : 4;
        bool reset : 1;
        bool timer : 1;
        bool snooker : 1;
        bool btnRed : 1;
        bool btnBlack : 1;
        bool btnPink : 1;
        bool btnBlue : 1;
        bool btnBrown : 1;
        bool btnGreen : 1;
        bool btnYellow : 1;
        bool btnWhiteRed : 1;
        bool btnWhiteBlack : 1;
    }
    btnState;
};

const uint8_t CRC = B1001;

const String BOARD_MESSAGE = "SCORE_BOARD:";

const String BOARD_MESSAGE_ACK = BOARD_MESSAGE + "OK";

const String BOARD_MESSAGE_INIT = BOARD_MESSAGE + "INIT";
