#ifndef _GUI_MAIN_H
#define _GUI_MAIN_H

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

extern volatile bool isTelegram;
extern volatile bool isAudio;

extern lv_obj_t* ui_ScreenMain;
extern lv_obj_t* ui_MBtnPool;
extern lv_obj_t* ui_MBtnLabelPool;
extern lv_obj_t* ui_MBtnSnooker;
extern lv_obj_t* ui_MBtnLabelSnooker;
extern lv_obj_t* ui_MBtnDarts;
extern lv_obj_t* ui_MBtnLabelDarts;
extern lv_obj_t* ui_MBtnLottery;
extern lv_obj_t* ui_MBtnLabelLottery;
extern lv_obj_t* ui_MBtnSettings;
extern lv_obj_t* ui_MBtnLabelSettings;
extern lv_obj_t* ui_MLabelLogo;
extern lv_obj_t* ui_MButtonAP;
extern lv_obj_t* ui_MLabelAP;
extern lv_obj_t* ui_MButtonWifi;
extern lv_obj_t* ui_MLabelWifi;
extern lv_obj_t* ui_MButtonTelegram;
extern lv_obj_t* ui_MLabelTelegram;
extern lv_obj_t* ui_MButtonMedical;
extern lv_obj_t* ui_MLabelMedical;
extern lv_obj_t* ui_MButtonAudio;
extern lv_obj_t* ui_MLabelAudio;

void gui_main_create();
void gui_main_delete();

#endif

