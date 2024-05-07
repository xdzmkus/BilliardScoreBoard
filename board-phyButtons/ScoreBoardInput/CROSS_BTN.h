#pragma once

#include <ArduinoDebounceButton.h>

class CROSS_BTN : public ArduinoDebounceButton
{
public:

    CROSS_BTN(uint8_t pin) : ArduinoDebounceButton(pin, BUTTON_CONNECTED::GND, BUTTON_NORMAL::CLOSE)
    {
    }

protected:

    virtual bool getPinState() override
    {
        return isBtnPressed();
    }

private:

    virtual bool isBtnPressed() = 0;
};

class SLEEP_BTN : public CROSS_BTN
{
public:

    SLEEP_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN5 - PIN1 connected

        // PIND = 111011xx
        // PINB = xxxxxxx0

        bool pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B11101100) && (bitRead(PINB, 0) == 0))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);

        return pressed;
    }
};

class UP_BTN : public CROSS_BTN
{
public:

    UP_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN2 - PIN1 connected

        // PIND = 011111xx
        // PINB = xxxxxxx0

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B01111100) && (bitRead(PINB, 0) == 0))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class AS_BTN : public CROSS_BTN
{
public:

    AS_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN3 - PIN2 connected

        // PIND = 001111xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B00111100) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class DOWN_BTN : public CROSS_BTN
{
public:

    DOWN_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN4 - PIN1 connected

        // PIND = 110111xx
        // PINB = xxxxxxx0

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B11011100) && (bitRead(PINB, 0) == 0))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class AL1_BTN : public CROSS_BTN
{
public:

    AL1_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN4 - PIN3 connected

        // PIND = 100111xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B10011100) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class CF_BTN : public CROSS_BTN
{
public:

    CF_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN5 - PIN3 connected

        // PIND = 101011xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B10101100) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class AL2_BTN : public CROSS_BTN
{
public:

    AL2_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN6 - PIN2 connected

        // PIND = 011101xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B01110100) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class POWER_BTN : public CROSS_BTN
{
public:

    POWER_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN6 - PIN5 connected

        // PIND = 111001xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B11100100) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

class MODE_BTN : public CROSS_BTN
{
public:

    MODE_BTN(uint8_t pin) : CROSS_BTN(pin)
    {
    }

private:

    virtual bool isBtnPressed() override
    {
        // PIN7 - PIN6 connected

        // PIND = 111100xx
        // PINB = xxxxxxx1

        boolean pressed = false;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);

        if (((PIND & B11111100) == B11110000) && (bitRead(PINB, 0) == 1))
            pressed = true;

        pinMode(pin, INPUT_PULLUP);
        return pressed;
    }
};

