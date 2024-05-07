#ifndef _SQUARELINE_UI_H
#define _SQUARELINE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("../libraries/lvgl/lvgl.h")
#include "../libraries/lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_comp_namekeyboard.h"
#include "ui_comp_panelpoolplayer.h"
#include "ui_comp_optionskeyboard.h"

typedef void (*ui_comp_cb_t)(lv_obj_t* obj);

extern uint32_t LV_EVENT_GET_COMP_CALLBACK;
extern uint32_t LV_EVENT_SET_COMP_CALLBACK;

ui_comp_cb_t ui_comp_get_callback(lv_obj_t* comp);
void ui_comp_set_callback(lv_obj_t* comp, ui_comp_cb_t cb);

void get_component_callback_event_cb(lv_event_t* e);
void set_component_callback_event_cb(lv_event_t* e);
void del_component_callback_event_cb(lv_event_t* e);

extern uint32_t LV_EVENT_GET_COMP_CHILD;
extern uint32_t LV_EVENT_SET_COMP_CHILD;

lv_obj_t* ui_comp_get_child(lv_obj_t* comp, uint32_t child_idx);
void ui_comp_set_child(lv_obj_t* comp, uint32_t child_idx, lv_obj_t* obj);

void get_component_child_event_cb(lv_event_t* e);
void set_component_child_event_cb(lv_event_t* e);
void del_component_child_event_cb(lv_event_t* e);

extern const char* cyrillic_kb_map_lc[];
extern const char* cyrillic_kb_map_uc[];
extern const lv_buttonmatrix_ctrl_t cyrillic_kb_ctrl_map[];

extern const char* latin_kb_map_lc[];
extern const char* latin_kb_map_uc[];
extern const lv_buttonmatrix_ctrl_t latin_kb_ctrl_map[];

extern const char* special_kb_map[];
extern const lv_buttonmatrix_ctrl_t special_kb_ctrl_map[];

extern const char* score_kb_map_num[];
extern const lv_buttonmatrix_ctrl_t score_kb_ctrl_num_map[];

void ui_event_KeyboardButtons(lv_event_t* e);
void ui_event_ScoreKeyboardButtons(lv_event_t* e);

LV_IMG_DECLARE(ui_img_snooker_table_480x320_png);
LV_IMG_DECLARE(ui_img_break_png);
LV_IMG_DECLARE(ui_img_break0_png);
LV_IMG_DECLARE(ui_img_break180_png);
LV_FONT_DECLARE(ui_font_UbuntuCyrillic25);
LV_FONT_DECLARE(ui_font_UbuntuDigits92);

#if !defined LV_SYMBOL_TELEGRAM
#define LV_SYMBOL_TELEGRAM  "\xEF\x8B\x86" /*0xF2C6*/
#endif

#if !defined LV_SYMBOL_AP
#define LV_SYMBOL_AP        "\xEF\x94\x99" /*0xF519*/
#endif

#if !defined LV_SYMBOL_MEDICAL
#define LV_SYMBOL_MEDICAL   "\xEF\x83\xB9" /*0xF0F9*/
#endif

#if !defined LV_SYMBOL_GLOBE
#define LV_SYMBOL_GLOBE     "\xEF\x82\xAC" /*0xF0AC*/
#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
