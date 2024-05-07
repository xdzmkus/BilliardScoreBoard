#pragma once

#include <Arduino.h>

bool setup_Audio();

void audio_turnOn();
void audio_turnOff();
void audio_reset();
void audio_say(int16_t word);
