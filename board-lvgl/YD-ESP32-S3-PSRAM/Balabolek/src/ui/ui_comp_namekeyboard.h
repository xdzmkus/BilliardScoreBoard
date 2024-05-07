#ifndef _UI_COMP_NAMEKEYBOARD_H
#define _UI_COMP_NAMEKEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ui.h"

#define UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD 0
#define UI_COMP_NAMEKEYBOARD_NAMELIST 1
#define UI_COMP_NAMEKEYBOARD_NAMETEXTAREA 2
#define UI_COMP_NAMEKEYBOARD_BUTTONCLOSE 3
#define UI_COMP_NAMEKEYBOARD_BUTTONCLOSE_LABELCLOSE 4
#define UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS 5
#define _UI_COMP_NAMEKEYBOARD_NUM 6

lv_obj_t * ui_NameKeyboard_create(lv_obj_t * comp_parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
