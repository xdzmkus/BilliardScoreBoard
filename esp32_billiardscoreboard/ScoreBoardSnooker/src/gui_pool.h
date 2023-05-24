#ifndef _GUI_POOL_H
#define _GUI_POOL_H

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

extern lv_obj_t* ui_ScreenPool;
extern lv_obj_t* ui_PLabelHome;
extern lv_obj_t* ui_PLabelRefresh;
extern lv_obj_t* ui_PSwitchPlyCount;
extern lv_obj_t* ui_PLabel2;
extern lv_obj_t* ui_PLabel3;
extern lv_obj_t* ui_PPanelPool2;
extern lv_obj_t* ui_PanelPool2Ply1;
extern lv_obj_t* ui_PImageBreak;
extern lv_obj_t* ui_PanelPool2Ply2;
extern lv_obj_t* ui_PPanelPool3;
extern lv_obj_t* ui_PanelPool3Ply1;
extern lv_obj_t* ui_PanelPool3Ply2;
extern lv_obj_t* ui_PanelPool3Ply3;

extern lv_obj_t* ui_PNameKeyboard;

void gui_pool_init();

String gui_pool_score();
String gui_pool_getHistory();
void gui_pool_restoreHistory(String& value, uint8_t idx);

void changeScore(lv_event_t* e);
void changeScorePlus(lv_event_t* e);
void changeScoreMinus(lv_event_t* e);
void changePlayerName(lv_event_t* e);

#endif

