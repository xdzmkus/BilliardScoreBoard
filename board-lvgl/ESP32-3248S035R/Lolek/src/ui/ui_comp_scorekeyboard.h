#ifndef _UI_COMP_SCOREKEYBOARD_H
#define _UI_COMP_SCOREKEYBOARD_H

#include "ui.h"

#ifdef __cplusplus
extern "C" {
#endif

// COMPONENT ScoreKeyboard
#define UI_COMP_SCOREKEYBOARD_SCOREKEYBOARD 0
#define UI_COMP_SCOREKEYBOARD_LABELUPDATEDSCORE 1
#define UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE 2
#define UI_COMP_SCOREKEYBOARD_KEYBOARDSCORE 3
#define _UI_COMP_SCOREKEYBOARD_NUM 4

lv_obj_t * ui_ScoreKeyboard_create(lv_obj_t * comp_parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
