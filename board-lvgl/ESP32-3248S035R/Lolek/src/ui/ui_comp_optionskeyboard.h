#ifndef _UI_COMP_OPTIONSKEYBOARD_H
#define _UI_COMP_OPTIONSKEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ui.h"

// COMPONENT OptionsKeyboard
#define UI_COMP_OPTIONSKEYBOARD_OPTIONSKEYBOARD 0
#define UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA 1
#define UI_COMP_OPTIONSKEYBOARD_BUTTONCLOSE 2
#define UI_COMP_OPTIONSKEYBOARD_BUTTONCLOSE_LABELCLOSE 3
#define UI_COMP_OPTIONSKEYBOARD_KEYBOARDBUTTONS 4
#define _UI_COMP_OPTIONSKEYBOARD_NUM 5

lv_obj_t * ui_OptionsKeyboard_create(lv_obj_t * comp_parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
