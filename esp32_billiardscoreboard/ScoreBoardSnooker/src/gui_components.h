#ifndef _GUI_COMPONENTS_H
#define _GUI_COMPONENTS_H

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

extern uint32_t LV_EVENT_GET_COMP_CHILD;
extern uint32_t LV_EVENT_SET_COMP_CHILD;

lv_obj_t* ui_comp_get_child(lv_obj_t* comp, uint32_t child_idx);
void ui_comp_set_child(lv_obj_t* comp, uint32_t child_idx, lv_obj_t* obj);

// COMPONENT NameKeyboard
#define UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD 0
#define UI_COMP_NAMEKEYBOARD_NAMELABEL 1
#define UI_COMP_NAMEKEYBOARD_NAMELIST 2
#define UI_COMP_NAMEKEYBOARD_NAMETEXTAREA 3
#define UI_COMP_NAMEKEYBOARD_BUTTONCLOSE 4
#define UI_COMP_NAMEKEYBOARD_BUTTONCLOSE_LABELCLOSE 5
#define UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS 6
#define _UI_COMP_NAMEKEYBOARD_NUM 7
lv_obj_t* ui_NameKeyboard_create(lv_obj_t* comp_parent);

// COMPONENT PanelPoolPlayer
#define UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER 0
#define UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE 1
#define UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYCHANGE 2
#define UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME 3
#define UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE 4
#define UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELPLUS 5
#define UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELMINUS 6
#define _UI_COMP_PANELPOOLPLAYER_NUM 7
lv_obj_t* ui_PanelPoolPlayer_create(lv_obj_t* comp_parent);


#endif
