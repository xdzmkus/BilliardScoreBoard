#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

bool setup_SDCARD();

void setup_Audio();

void sayGameResult(int16_t first, int16_t second);
void sayGameResult(int16_t first, int16_t second, int16_t third);
void sayFrameResult(int16_t first, int16_t second);

void activateAudio();
void deactivateAudio();

