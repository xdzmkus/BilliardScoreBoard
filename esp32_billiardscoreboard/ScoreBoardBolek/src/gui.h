#ifndef _GUI_H
#define _GUI_H

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

extern uint16_t snookerPly1Scores;
extern uint16_t snookerPly2Scores;

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
} SNOOKER_ACTION;

#define MAX_ACTIONS 1024						// maximum amount of actions

extern SNOOKER_ACTION historyActions[MAX_ACTIONS];		// list of actions

extern uint16_t numberActions;						// number of executed actions

extern int16_t pool2Ply1Score;
extern int16_t pool2Ply2Score;
extern int16_t pool3Ply1Score;
extern int16_t pool3Ply2Score;
extern int16_t pool3Ply3Score;

typedef	enum
{
    LEFT = 0,
    RIGHT = 1800
} POOL_PLAYER_BREAK;

extern POOL_PLAYER_BREAK poolPlyBreak;

typedef	enum
{
    TWO = 0,
    THREE = 1
} POOL_PLAYER_COUNT;

extern POOL_PLAYER_COUNT poolPlyCount;

void gui_init();

void gui_disableAudio();
bool gui_isAudioDisabled();

String gui_getState();
void gui_restoreState(String& value, uint8_t idx);

#endif

