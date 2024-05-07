#pragma once

#include <Arduino.h>

bool touchpad_read(int32_t& x, int32_t& y);
void setup_Touch(uint8_t rotation);
