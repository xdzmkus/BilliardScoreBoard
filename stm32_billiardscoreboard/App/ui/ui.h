// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.3.4
// PROJECT: SquareLine_Pool3

#ifndef _SQUARELINE_POOL3_UI_H
#define _SQUARELINE_POOL3_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lvgl/lvgl.h"

#define MSG_TIME_CHANGED 100
#define MSG_SWITCH_CHANGED 101

void ui_event_Screen0(lv_event_t * e);
extern lv_obj_t * ui_Screen0;
extern lv_obj_t * ui_Time;
void ui_event_ResetBTN(lv_event_t * e);
extern lv_obj_t * ui_ResetBTN;

void ui_event_Screen1(lv_event_t * e);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_Label1P;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label1M;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_Label2P;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label2M;
extern lv_obj_t * ui_Switch;

void ui_event_Screen2(lv_event_t * e);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_Label3P;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label3M;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_Label4P;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label4M;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_Label5P;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Label5M;

LV_IMG_DECLARE(ui_img_icn_history_png);

LV_FONT_DECLARE(ui_font_Ubuntu80Digits);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
