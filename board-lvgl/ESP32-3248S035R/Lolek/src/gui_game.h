#ifndef _GUI_GAME_H
#define _GUI_GAME_H

#include "ui/ui.h"

extern lv_obj_t* ui_ScreenGame;

void gui_game_create();

#ifdef __cplusplus
extern "C" {
#endif

void changeName(lv_event_t* e);
void changeScore(lv_event_t* e);
void changeScorePlus(lv_event_t* e);
void changeScoreMinus(lv_event_t* e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

