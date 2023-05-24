#ifndef _GUI_SETTINGS_H
#define _GUI_SETTINGS_H

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

extern lv_obj_t* ui_ScreenSettings;
extern lv_obj_t* ui_SLabelHome;
extern lv_obj_t* ui_SLabelRefresh;
extern lv_obj_t* ui_SPanelSettings;
extern lv_obj_t* ui_SPanelPoolPlayers;
extern lv_obj_t* ui_SLabelPlayers;
extern lv_obj_t* ui_SPanelPly1;
extern lv_obj_t* ui_SLabelNumberPly1;
extern lv_obj_t* ui_SLabelNamePly1;
extern lv_obj_t* ui_SButtonEditPly1;
extern lv_obj_t* ui_SLabelEditPly1;
extern lv_obj_t* ui_SPanelPly2;
extern lv_obj_t* ui_SLabelNumberPly2;
extern lv_obj_t* ui_SLabelNamePly2;
extern lv_obj_t* ui_SButtonEditPly2;
extern lv_obj_t* ui_SLabelEditPly2;
extern lv_obj_t* ui_SPanelPly3;
extern lv_obj_t* ui_SLabelNumberPly3;
extern lv_obj_t* ui_SLabelNamePly3;
extern lv_obj_t* ui_SButtonEditPly3;
extern lv_obj_t* ui_SLabelEditPly3;
extern lv_obj_t* ui_SPanelSnooker;
extern lv_obj_t* ui_SLabelSnooker;
extern lv_obj_t* ui_SLabel6Red;
extern lv_obj_t* ui_SSwitch6Red;
extern lv_obj_t* ui_SLabelHandicap1;
extern lv_obj_t* ui_STextAreaHandicap1;
extern lv_obj_t* ui_SLabelHandicap2;
extern lv_obj_t* ui_STextAreaHandicap2;
extern lv_obj_t* ui_SButtonSnookerSave;
extern lv_obj_t* ui_SLabelSnookerSave;
extern lv_obj_t* ui_SPanelDateTime;
extern lv_obj_t* ui_SLabelDate;
extern lv_obj_t* ui_STextAreaDate;
extern lv_obj_t* ui_SLabelTime;
extern lv_obj_t* ui_SRollerHours;
extern lv_obj_t* ui_SLabelTimeDots;
extern lv_obj_t* ui_SRollerMinutes;
extern lv_obj_t* ui_SButtonTimeSave;
extern lv_obj_t* ui_SLabelTimeSave;
extern lv_obj_t* ui_SPanelWelcome;
extern lv_obj_t* ui_SLabelWelcome;
extern lv_obj_t* ui_SLabelGreeting;
extern lv_obj_t* ui_SButtonEditGreeting;
extern lv_obj_t* ui_SLabelEditGreeting;
extern lv_obj_t* ui_SButtonSaveGreeting;
extern lv_obj_t* ui_SLabelSaveGreeting;

extern lv_obj_t* ui_SNameKeyboard;
extern lv_obj_t* ui_SCalendar;
extern lv_obj_t* ui_SKeyboard;

void gui_settings_init();

#endif

