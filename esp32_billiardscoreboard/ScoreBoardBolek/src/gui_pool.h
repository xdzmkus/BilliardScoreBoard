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

extern lv_obj_t* ui_MBPanelPool;
extern lv_obj_t* ui_MBLabelPoolResetQ;
extern lv_obj_t* ui_MBBtnPoolResetYes;
extern lv_obj_t* ui_MBLabelPoolResetYes;
extern lv_obj_t* ui_MBBtnPoolResetNo;
extern lv_obj_t* ui_MBLabelPoolResetNo;


extern int16_t pool2Ply1Score;
extern int16_t pool2Ply2Score;
extern int16_t pool3Ply1Score;
extern int16_t pool3Ply2Score;
extern int16_t pool3Ply3Score;


void gui_pool_create();
void gui_pool_delete();

String gui_pool_getPollQuestion();
String gui_pool_getScore();

void changeScore(lv_event_t* e);
void changeScorePlus(lv_event_t* e);
void changeScoreMinus(lv_event_t* e);
void changePlayerName(lv_event_t* e);

#endif

