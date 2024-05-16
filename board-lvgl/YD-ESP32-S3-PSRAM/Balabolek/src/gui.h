#ifndef _GUI_H
#define _GUI_H

#include <Arduino.h>

#include "ui/ui.h"

extern SemaphoreHandle_t gui_mutex;

enum GAME_PLAYER_NAME
{
    DARTS_PLAYER1,
    DARTS_PLAYER2,
    DARTS_PLAYER3,
    PLAYER1,
    PLAYER2,
    PLAYER_EX1,
    PLAYER_EX2,
    PLAYER_EX3
};

enum GAME_PLAYER_BREAK
{
    LEFT = 1,
    RIGHT = 2
};

enum GAME_PLAYER_COUNT
{
    TWO = 0,
    THREE = 1
};

enum SNOOKER_ACTION : uint8_t
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
};

#define MAX_ACTIONS 1024						    // maximum amount of actions
extern SNOOKER_ACTION* historyActions;	            // list of actions
extern uint16_t numberActions;						// number of executed actions

struct BoardState_Publishing
{
    char* dartsPlayer1name;
    char* dartsPlayer2name;
    char* dartsPlayer3name;
    char* player1name;
    char* player2name;
    int16_t gamePly1Score;
    int16_t gamePly2Score;
    GAME_PLAYER_BREAK gamePlyBreak;
    GAME_PLAYER_COUNT gamePlyCount;
    char* playerEx1name;
    char* playerEx2name;
    char* playerEx3name;
    int16_t gameExPly1Score;
    int16_t gameExPly2Score;
    int16_t gameExPly3Score;
    int16_t tvGameScorePly1;
    int16_t tvGameScorePly2;
    int16_t tvGameScoreMax;
    int16_t tvFrameScorePly1;
    int16_t tvFrameScorePly2;
    uint8_t snookerPly1Handicap;
    uint8_t snookerPly2Handicap;
    bool snookerControlBalls;
    bool snooker6Red;
    uint16_t snookerPly1Scores;
    uint16_t snookerPly2Scores;
};

extern BoardState_Publishing boardPublishing;

extern bool gameHasSatrted;

void gui_init();

const char* gui_getPlayerName(GAME_PLAYER_NAME player);
void gui_setPlayerName(GAME_PLAYER_NAME dst, const char* src);

void gui_turnAP(boolean state);
void gui_turnWiFi(boolean state);
void gui_turnTelegram(boolean state);
void gui_turnAudio(boolean state);
void gui_setVolume(uint8_t volume);

float gui_getVolumeInRange(float out_min, float out_max);

bool gui_stateAwaiting();
void gui_stateRequest();
void gui_stateRevoke();

bool gui_wifiIsEnabledAndConnected();

void gui_publishCurrentState();
void gui_restoreCurrentState(char* state);

void gui_sendTelegaPollMessage(GAME_PLAYER_COUNT cnt);
void gui_sendTelegaGameScoreMessage(GAME_PLAYER_COUNT cnt);
void gui_sendTelegaFrameScoreMessage(bool update = true);
void gui_sendTelegaTVGameScoreMessage();
void gui_sendTelegaTVFrameScoreMessage(bool update = true);

void gui_sayLot(uint8_t lot);
void gui_sayGameResult(GAME_PLAYER_COUNT cnt);
void gui_sayFrameResult();
void gui_sayTVGameResult();
void gui_sayTVFrameResult();

#endif

