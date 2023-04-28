// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.3
// LVGL version: 8.2.0
// Project name: SquareLine_Pool

#ifndef _SQUARELINE_UI_H
#define _SQUARELINE_UI_H

#ifdef __cplusplus
extern "C" {
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

LV_IMG_DECLARE(ui_img_snooker_table_480x320_png);    // assets\snooker_table_480x320.png
LV_IMG_DECLARE(ui_img_break_png);    // assets\break.png
LV_FONT_DECLARE(ui_font_UbuntuCyrillic25);
LV_FONT_DECLARE(ui_font_UbuntuDigits92);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
