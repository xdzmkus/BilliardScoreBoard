#ifndef _GUI_LOTTERY_H
#define _GUI_LOTTERY_H

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

    extern lv_obj_t* ui_ScreenLottery;
    extern lv_obj_t* ui_LRollerLots;
    extern lv_obj_t* ui_LPanelLot;
    extern lv_obj_t* ui_LLabelLot;
    extern lv_obj_t* ui_LPanelLottery;
    extern lv_obj_t* ui_LLabelLottery;
    extern lv_obj_t* ui_LPanelListLots;
    extern lv_obj_t* ui_LLabelListLots;
    extern lv_obj_t* ui_LLabelHome;
    extern lv_obj_t* ui_LLabelRefresh;

    void gui_lottery_init();

#endif

