#ifndef _GUI_H
#define _GUI_H

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern bool gui_rtc_save;

extern uint8_t	gui_date_day;
extern uint8_t	gui_date_month;
extern uint16_t gui_date_year;

extern uint8_t	gui_time_hours;
extern uint8_t	gui_time_minutes;

bool gui_get_telegram_send();

void gui_update_date();

void gui_init();

#endif

