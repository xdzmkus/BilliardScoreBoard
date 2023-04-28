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

    extern lv_obj_t* ui_ScreenMain;
    extern lv_obj_t* ui_MBtnPool;
    extern lv_obj_t* ui_MBtnLabelPool;
    extern lv_obj_t* ui_MBtnSnooker;
    extern lv_obj_t* ui_MBtnLabelSnooker;
    extern lv_obj_t* ui_MBtnLottery;
    extern lv_obj_t* ui_MBtnLabelLottery;
    extern lv_obj_t* ui_MBtnSettings;
    extern lv_obj_t* ui_MBtnLabelSettings;
    extern lv_obj_t* ui_MLabelLogo;
    extern lv_obj_t* ui_MLabelDate;
    extern lv_obj_t* ui_MLabelTime;
    extern lv_obj_t* ui_MLabelTimeRefresh;

    void gui_main_init(void);

    void gui_main_updateTime(const char* newTime);

#endif

