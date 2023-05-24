#ifndef _GUI_SNOOKER_H
#define _GUI_SNOOKER_H

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

extern lv_obj_t* ui_ScreenSnooker;
extern lv_obj_t* ui_NLabelHome;
extern lv_obj_t* ui_NLabelRefresh;
extern lv_obj_t* ui_NRestYellow;
extern lv_obj_t* ui_NRestGreen;
extern lv_obj_t* ui_NRestBrown;
extern lv_obj_t* ui_NRestBlue;
extern lv_obj_t* ui_NRestPink;
extern lv_obj_t* ui_NRestBlack;
extern lv_obj_t* ui_NRestRed;
extern lv_obj_t* ui_NLabelRestRed;
extern lv_obj_t* ui_NPanelPly1;
extern lv_obj_t* ui_NPlyLabelName1;
extern lv_obj_t* ui_NPlyLabelScore1;
extern lv_obj_t* ui_NPlyLabelMaxScore1;
extern lv_obj_t* ui_NPlyLabelMax1;
extern lv_obj_t* ui_NPanelPlyBreak;
extern lv_obj_t* ui_NLabelPlyBreak;
extern lv_obj_t* ui_NPanelPly2;
extern lv_obj_t* ui_NPlyLabelName2;
extern lv_obj_t* ui_NPlyLabelScore2;
extern lv_obj_t* ui_NPlyLabelMaxScore2;
extern lv_obj_t* ui_NPlyLabelMax2;
extern lv_obj_t* ui_NButtonCancel;
extern lv_obj_t* ui_NLabelCancel;

extern lv_obj_t* ui_NNameKeyboard;

typedef	enum
{
    PLAYER1,
    PLAYER2
} SNOOKER_PLAYER;

typedef	enum
{
    P1_MISS,
    P1_RED,
    P1_BLACK,
    P1_PINK,
    P1_BLUE,
    P1_BROWN,
    P1_GREEN,
    P1_YELLOW,
    P1_F_RED,
    P1_F_PINK,
    P1_F_BLUE,
    P1_F_BROWN,
    P1_F_GREEN,
    P1_F_YELLOW,
    P1_FOUL_4,
    P1_FOUL_5,
    P1_FOUL_6,
    P1_FOUL_7,
    P2_MISS,
    P2_RED,
    P2_BLACK,
    P2_PINK,
    P2_BLUE,
    P2_BROWN,
    P2_GREEN,
    P2_YELLOW,
    P2_F_RED,
    P2_F_PINK,
    P2_F_BLUE,
    P2_F_BROWN,
    P2_F_GREEN,
    P2_F_YELLOW,
    P2_FOUL_4,
    P2_FOUL_5,
    P2_FOUL_6,
    P2_FOUL_7,
    P_FLUKE_RED
}
SNOOKER_ACTION;

void gui_snooker_init();

String gui_snooker_score();

String gui_snooker_getHistory();
void gui_snooker_restoreHistory(String& value, uint8_t idx);

SNOOKER_PLAYER gui_snooker_get_activePlayer();

void gui_snooker_pushAction(SNOOKER_ACTION sAction);

bool gui_snooker_isFreeBallPossible();
bool gui_snooker_isRedBallPossible();
bool gui_snooker_isBlackBallPossible();
bool gui_snooker_isPinkBallPossible();
bool gui_snooker_isBlueBallPossible();
bool gui_snooker_isBrownBallPossible();
bool gui_snooker_isGreenBallPossible();
bool gui_snooker_isYellowBallPossible();

void gui_snooker_setHandicapP1(uint16_t handicap);
void gui_snooker_setHandicapP2(uint16_t handicap);
void gui_snooker_set6Red(bool is6Red);

#endif

