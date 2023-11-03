#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

bool touchpad_read(int16_t& x, int16_t& y);
void setup_Touch(uint8_t rotation);
