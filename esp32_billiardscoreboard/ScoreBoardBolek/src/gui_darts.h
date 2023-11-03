#ifndef _GUI_DARTS_H
#define _GUI_DARTS_H

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
extern lv_obj_t* ui_ScreenDarts;
extern lv_obj_t* ui_DPanelPlayers;
extern lv_obj_t* ui_DPanelPly1;
extern lv_obj_t* ui_DLabelPly1;
extern lv_obj_t* ui_DPanelPly2;
extern lv_obj_t* ui_DLabelPly2;
extern lv_obj_t* ui_DPanelPly3;
extern lv_obj_t* ui_DLabelPly3;
extern lv_obj_t* ui_DPanelGame;
extern lv_obj_t* ui_DLabelSuggest;
extern lv_obj_t* ui_DLabelScore;
extern lv_obj_t* ui_DPanelHistory;
extern lv_obj_t* ui_DLabelHistory;
extern lv_obj_t* ui_DButtonSector;
extern lv_obj_t* ui_DLabelSector;
extern lv_obj_t* ui_DButtonDouble;
extern lv_obj_t* ui_DLabelDouble;
extern lv_obj_t* ui_DButtonTriple;
extern lv_obj_t* ui_DLabelTriple;
extern lv_obj_t* ui_DLabelHome;
extern lv_obj_t* ui_DLabelReset;
extern lv_obj_t* ui_DLabelTrash;
extern lv_obj_t* ui_DPanelReset;
extern lv_obj_t* ui_DLabelNew;
extern lv_obj_t* ui_DButtonYes;
extern lv_obj_t* ui_DLabelYes;
extern lv_obj_t* ui_DButtonNo;
extern lv_obj_t* ui_DLabelNo;
extern lv_obj_t* ui_DPanelRemove;
extern lv_obj_t* ui_DLabelRemove;
extern lv_obj_t* ui_DButtonRemoveYes;
extern lv_obj_t* ui_DLabelRemoveYes;
extern lv_obj_t* ui_DButtonRemoveNo;
extern lv_obj_t* ui_DLabelRemoveNo;
extern lv_obj_t* ui_DPanelKB;
extern lv_obj_t* ui_DTextArea;
extern lv_obj_t* ui_DKeyboard;

void gui_darts_create();
void gui_darts_delete();


#endif

