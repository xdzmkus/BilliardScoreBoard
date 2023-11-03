#include "gui_snooker.h"
#include "gui.h"
#include "gui_main.h"
#include "gui_settings.h"
#include "gui_pool.h"

#include "TaskNetwork.h"
#include "TaskAudio.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// Balls part

lv_obj_t* ui_BPanelBalls;
lv_obj_t* ui_BButtonRed;
lv_obj_t* ui_BLabel1;
lv_obj_t* ui_BButtonBlack;
lv_obj_t* ui_BLabel7;
lv_obj_t* ui_BButtonPink;
lv_obj_t* ui_BLabel6;
lv_obj_t* ui_BButtonBlue;
lv_obj_t* ui_BLabel5;
lv_obj_t* ui_BButtonBrown;
lv_obj_t* ui_BLabel4;
lv_obj_t* ui_BButtonGreen;
lv_obj_t* ui_BLabel3;
lv_obj_t* ui_BButtonYellow;
lv_obj_t* ui_BLabel2;
lv_obj_t* ui_BButtonMiss;
lv_obj_t* ui_BLabel0;
lv_obj_t* ui_BButtonFoul;
lv_obj_t* ui_BLabelFoul;
lv_obj_t* ui_BButtonFreeBall;
lv_obj_t* ui_BLabelFreeBall;
lv_obj_t* ui_BButtonCancel;
lv_obj_t* ui_BLabelCancel;
lv_obj_t* ui_BPanelFree;
lv_obj_t* ui_BButtonRedF;
lv_obj_t* ui_BLabelFB1;
lv_obj_t* ui_BButtonYellowF;
lv_obj_t* ui_BLabelFB2;
lv_obj_t* ui_BButtonGreenF;
lv_obj_t* ui_BLabelFB3;
lv_obj_t* ui_BButtonBrownF;
lv_obj_t* ui_BLabelFB4;
lv_obj_t* ui_BButtonBlueF;
lv_obj_t* ui_BLabelFB5;
lv_obj_t* ui_BButtonPinkF;
lv_obj_t* ui_BLabelFB6;
lv_obj_t* ui_BPanelFoul;
lv_obj_t* ui_BButtonF4;
lv_obj_t* ui_BLabelF4;
lv_obj_t* ui_BButtonF5;
lv_obj_t* ui_BLabelF5;
lv_obj_t* ui_BButtonF6;
lv_obj_t* ui_BLabelF6;
lv_obj_t* ui_BButtonF7;
lv_obj_t* ui_BLabelF7;
lv_obj_t* ui_BButtonF1;
lv_obj_t* ui_BLabelF1;

lv_obj_t* ui_MBPanelSnookerYellow;
lv_obj_t* ui_MBLabelSnookerYellowQ;
lv_obj_t* ui_MBBtnSnookerYellowYes;
lv_obj_t* ui_MBLabelSnookerYellowYes;
lv_obj_t* ui_MBBtnSnookerYellowNo;
lv_obj_t* ui_MBLabelSnookerYellowNo;

// Snooker part

lv_obj_t* ui_ScreenSnooker;
lv_obj_t* ui_NLabelHome;
lv_obj_t* ui_NLabelRefresh;
lv_obj_t* ui_NRestYellow;
lv_obj_t* ui_NRestGreen;
lv_obj_t* ui_NRestBrown;
lv_obj_t* ui_NRestBlue;
lv_obj_t* ui_NRestPink;
lv_obj_t* ui_NRestBlack;
lv_obj_t* ui_NRestRed;
lv_obj_t* ui_NLabelRestRed;
lv_obj_t* ui_NLabelRestScore;
lv_obj_t* ui_NPanelPly1;
lv_obj_t* ui_NPlyLabelName1;
lv_obj_t* ui_NPlyLabelScore1;
lv_obj_t* ui_NPlyLabelMaxScore1;
lv_obj_t* ui_NPlyLabelDiff1;
lv_obj_t* ui_NPanelPlyBreak;
lv_obj_t* ui_NLabelPlyBreak;
lv_obj_t* ui_NPanelPly2;
lv_obj_t* ui_NPlyLabelName2;
lv_obj_t* ui_NPlyLabelScore2;
lv_obj_t* ui_NPlyLabelMaxScore2;
lv_obj_t* ui_NPlyLabelDiff2;
lv_obj_t* ui_NButtonCancel;
lv_obj_t* ui_NLabelCancel;

lv_obj_t* ui_MBPanelSnookerReset;
lv_obj_t* ui_MBLabelSnookerResetQ;
lv_obj_t* ui_MBBtnSnookerResetYes;
lv_obj_t* ui_MBLabelSnookerResetYes;
lv_obj_t* ui_MBBtnSnookerResetNo;
lv_obj_t* ui_MBLabelSnookerResetNo;
lv_obj_t* ui_MBPanelSnookerPool;
lv_obj_t* ui_MBLabelSnookerPoolQ;
lv_obj_t* ui_MBBtnSnookerPoolYes;
lv_obj_t* ui_MBLabelSnookerPoolYes;
lv_obj_t* ui_MBBtnSnookerPoolNo;
lv_obj_t* ui_MBLabelSnookerPoolNo;


#define COLOR_RED "F20000"
#define COLOR_BLACK "000000"
#define COLOR_PINK "E781DF"
#define COLOR_BLUE "0F00FF"
#define COLOR_BROWN "75690A"
#define COLOR_GREEN "208E02"
#define COLOR_YELLOW "D2DD15"


static SNOOKER_PLAYER activePlayer;					// player who made last action

static struct BALLS
{
    int8_t red;
    int8_t black;
    int8_t pink;
    int8_t blue;
    int8_t brown;
    int8_t green;
    int8_t yellow;
} ballsTable;

static bool _isControl = true;
static bool _is6Red = false;

///////////////////// FUNCTIONS ////////////////////

static void ui_calculateScores()
{
    char* output;

    snookerPly1Scores = strtoul(lv_textarea_get_text(ui_STextAreaHandicap1), &output, 10);
    snookerPly2Scores = strtoul(lv_textarea_get_text(ui_STextAreaHandicap2), &output, 10);

    if (_is6Red)
    {
        ballsTable =
        {
            .red = 6,
            .black = 1,
            .pink = 1,
            .blue = 1,
            .brown = 1,
            .green = 1,
            .yellow = 1
        };
    }
    else
    {
        ballsTable =
        {
            .red = 15,
            .black = 1,
            .pink = 1,
            .blue = 1,
            .brown = 1,
            .green = 1,
            .yellow = 1
        };
    }
    
    String plySeries = "=  =\n";

    // Calculate player's scores
    for (uint16_t i = 0; i < numberActions; i++)
    {
        switch (historyActions[i])
        {
            // PLAYER1
        case P1_MISS:
            plySeries += "-\n";
            break;
        case P1_RED:
            ballsTable.red--;
            snookerPly1Scores += 1;
            plySeries += "#" COLOR_RED " 1#\n";
            break;
        case P1_BLACK:
            if (ballsTable.pink == 0) ballsTable.black--;
            snookerPly1Scores += 7;
            plySeries += "#" COLOR_BLACK " 7#\n";
            break;
        case P1_PINK:
            if (ballsTable.blue == 0) ballsTable.pink--;
            snookerPly1Scores += 6;
            plySeries += "#" COLOR_PINK " 6#\n";
            break;
        case P1_BLUE:
            if (ballsTable.brown == 0) ballsTable.blue--;
            snookerPly1Scores += 5;
            plySeries += "#" COLOR_BLUE " 5#\n";
            break;
        case P1_BROWN:
            if (ballsTable.green == 0) ballsTable.brown--;
            snookerPly1Scores += 4;
            plySeries += "#" COLOR_BROWN " 4#\n";
            break;
        case P1_GREEN:
            if (ballsTable.yellow == 0) ballsTable.green--;
            snookerPly1Scores += 3;
            plySeries += "#" COLOR_GREEN " 3#\n";
            break;
        case P1_YELLOW:
            if (ballsTable.red == 0 && historyActions[i-1] != P1_RED) ballsTable.yellow--;
            snookerPly1Scores += 2;
            plySeries += "#" COLOR_YELLOW " 2#\n";
            break;
        case P1_F_RED:
            snookerPly1Scores += 1;
            plySeries += "#" COLOR_RED " 1.#\n";
            break;
        case P1_F_PINK:
            snookerPly1Scores += 6;
            plySeries += "#" COLOR_PINK " 6.#\n";
            break;
        case P1_F_BLUE:
            snookerPly1Scores += 5;
            plySeries += "#" COLOR_BLUE " 5.#\n";
            break;
        case P1_F_BROWN:
            snookerPly1Scores += 4;
            plySeries += "#" COLOR_BROWN " 4.#\n";
            break;
        case P1_F_GREEN:
            snookerPly1Scores += 3;
            plySeries += "#" COLOR_GREEN " 3.#\n";
            break;
        case P1_F_YELLOW:
            snookerPly1Scores += 2;
            plySeries += "#" COLOR_YELLOW " 2.#\n";
            break;
        case P1_FOUL_4:
            snookerPly1Scores += 4;
            plySeries += "4+\n";
            break;
        case P1_FOUL_5:
            snookerPly1Scores += 5;
            plySeries += "5+\n";
            break;
        case P1_FOUL_6:
            snookerPly1Scores += 6;
            plySeries += "6+\n";
            break;
        case P1_FOUL_7:
            snookerPly1Scores += 7;
            plySeries += "7+\n";
            break;
            // PLAYER2
        case P2_MISS:
            plySeries += "     -\n";
            break;
        case P2_RED:
            ballsTable.red--;
            snookerPly2Scores += 1;
            plySeries += "#" COLOR_RED "     1#\n";
            break;
        case P2_BLACK:
            if (ballsTable.pink == 0) ballsTable.black--;
            snookerPly2Scores += 7;
            plySeries += "#" COLOR_BLACK "     7#\n";
            break;
        case P2_PINK:
            if (ballsTable.blue == 0) ballsTable.pink--;
            snookerPly2Scores += 6;
            plySeries += "#" COLOR_PINK "     6#\n";
            break;
        case P2_BLUE:
            if (ballsTable.brown == 0) ballsTable.blue--;
            snookerPly2Scores += 5;
            plySeries += "#" COLOR_BLUE "     5#\n";
            break;
        case P2_BROWN:
            if (ballsTable.green == 0) ballsTable.brown--;
            snookerPly2Scores += 4;
            plySeries += "#" COLOR_BROWN "     4#\n";
            break;
        case P2_GREEN:
            if (ballsTable.yellow == 0) ballsTable.green--;
            snookerPly2Scores += 3;
            plySeries += "#" COLOR_GREEN "     3#\n";
            break;
        case P2_YELLOW:
            if (ballsTable.red == 0 && historyActions[i - 1] != P2_RED) ballsTable.yellow--;
            snookerPly2Scores += 2;
            plySeries += "#" COLOR_YELLOW "     2#\n";
            break;
        case P2_F_RED:
            snookerPly2Scores += 1;
            plySeries += "#" COLOR_RED "    .1#\n";
            break;
        case P2_F_PINK:
            snookerPly2Scores += 6;
            plySeries += "#" COLOR_PINK "    .6#\n";
            break;
        case P2_F_BLUE:
            snookerPly2Scores += 5;
            plySeries += "#" COLOR_BLUE "    .5#\n";
            break;
        case P2_F_BROWN:
            snookerPly2Scores += 4;
            plySeries += "#" COLOR_BROWN "    .4#\n";
            break;
        case P2_F_GREEN:
            snookerPly2Scores += 3;
            plySeries += "#" COLOR_GREEN "    .3#\n";
            break;
        case P2_F_YELLOW:
            snookerPly2Scores += 2;
            plySeries += "#" COLOR_YELLOW "    .2#\n";
            break;
        case P2_FOUL_4:
            snookerPly2Scores += 4;
            plySeries += "  +4\n";
            break;
        case P2_FOUL_5:
            snookerPly2Scores += 5;
            plySeries += "  +5\n";
            break;
        case P2_FOUL_6:
            snookerPly2Scores += 6;
            plySeries += "  +6\n";
            break;
        case P2_FOUL_7:
            snookerPly2Scores += 7;
            plySeries += "  +7\n";
            break;
        case P_FLUKE_RED:
            ballsTable.red--;
            plySeries += " -#" COLOR_RED " 1#-\n";
            break;
        default:
            break;
        }
    }

    // Show series
    lv_label_set_text(ui_NLabelPlyBreak, plySeries.c_str());
    lv_obj_scroll_to_y(ui_NPanelPlyBreak, lv_obj_get_height(ui_NLabelPlyBreak), LV_ANIM_OFF);

    // Show scores
    lv_label_set_text_fmt(ui_NPlyLabelScore1, "%d", snookerPly1Scores);
    lv_label_set_text_fmt(ui_NPlyLabelScore2, "%d", snookerPly2Scores);

    // Calculate differencies
    lv_label_set_text_fmt(ui_NPlyLabelDiff1, "%+d", snookerPly1Scores - snookerPly2Scores);
    lv_label_set_text_fmt(ui_NPlyLabelDiff2, "%+d", snookerPly2Scores - snookerPly1Scores);

    if (_isControl && ballsTable.red >= 0 && ballsTable.yellow >= 0 && ballsTable.green >= 0 && ballsTable.brown >= 0 && ballsTable.blue >= 0 && ballsTable.pink >= 0 && ballsTable.black >= 0)
    {
        // Calculate open scores
        uint8_t scoresOnTable = 8 * ballsTable.red + 7 * ballsTable.black + 6 * ballsTable.pink + 5 * ballsTable.blue + 4 * ballsTable.brown + 3 * ballsTable.green + 2 * ballsTable.yellow;
        lv_label_set_text_fmt(ui_NLabelRestScore, "%d", scoresOnTable);

        // Calculate max series
        uint16_t ply1Max = snookerPly1Scores + scoresOnTable;
        uint16_t ply2Max = snookerPly2Scores + scoresOnTable;

        if (numberActions > 0)
        {
            if (historyActions[numberActions - 1] == P1_RED || historyActions[numberActions - 1] == P1_F_RED)
                ply1Max += 7;
            if (historyActions[numberActions - 1] == P2_RED || historyActions[numberActions - 1] == P2_F_RED)
                ply2Max += 7;
        }

        // Show max series
        lv_label_set_text_fmt(ui_NPlyLabelMaxScore1, "%d", ply1Max);
        lv_label_set_text_fmt(ui_NPlyLabelMaxScore2, "%d", ply2Max);

        if (snookerPly1Scores + scoresOnTable < snookerPly2Scores) lv_obj_add_state(ui_NPlyLabelScore1, LV_STATE_USER_1);
        else lv_obj_clear_state(ui_NPlyLabelScore1, LV_STATE_USER_1);
        if (snookerPly2Scores + scoresOnTable < snookerPly1Scores) lv_obj_add_state(ui_NPlyLabelScore2, LV_STATE_USER_1);
        else lv_obj_clear_state(ui_NPlyLabelScore2, LV_STATE_USER_1);

        // Show available balls
        if (ballsTable.red == 0)
        {
            lv_label_set_text(ui_NLabelRestRed, "");
        }
        else
        {
            lv_label_set_text_fmt(ui_NLabelRestRed, "%d", ballsTable.red);
        }

        _ui_flag_modify(ui_NRestRed, LV_OBJ_FLAG_HIDDEN, ballsTable.red > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestBlack, LV_OBJ_FLAG_HIDDEN, ballsTable.black > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestPink, LV_OBJ_FLAG_HIDDEN, ballsTable.pink > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestBlue, LV_OBJ_FLAG_HIDDEN, ballsTable.blue > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestBrown, LV_OBJ_FLAG_HIDDEN, ballsTable.brown > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestGreen, LV_OBJ_FLAG_HIDDEN, ballsTable.green > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_NRestYellow, LV_OBJ_FLAG_HIDDEN, ballsTable.yellow > 0 ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
    }
    else
    {
        lv_obj_clear_state(ui_NPlyLabelScore1, LV_STATE_USER_1);
        lv_obj_clear_state(ui_NPlyLabelScore2, LV_STATE_USER_1);

        lv_label_set_text(ui_NLabelRestScore, "");
        lv_label_set_text(ui_NPlyLabelMaxScore1, "");
        lv_label_set_text(ui_NPlyLabelMaxScore2, "");

        lv_label_set_text(ui_NLabelRestRed, "");
        _ui_flag_modify(ui_NRestRed, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestBlack, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestPink, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestBlue, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestBrown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_NRestYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static SNOOKER_PLAYER gui_snooker_get_activePlayer()
{
    return activePlayer;
}

static void gui_snooker_pushAction(SNOOKER_ACTION sAction)
{
    // Save action
    historyActions[numberActions++] = sAction;

    ui_calculateScores();

    if (sAction != P1_MISS && sAction != P2_MISS && sAction != P_FLUKE_RED)
    {
        publishCurrentState();
        sendTelegaMessage(T_SNOOKER_MESSAGE_UPD, gui_snooker_getScoreMessage());
        sayFrameResult(snookerPly1Scores, snookerPly2Scores);
    }
}

static bool gui_snooker_isFreeBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_FOUL_4:
    case P1_FOUL_5:
    case P1_FOUL_6:
    case P1_FOUL_7:
        if (activePlayer == PLAYER1) return true;
        else return false;
    case P2_FOUL_4:
    case P2_FOUL_5:
    case P2_FOUL_6:
    case P2_FOUL_7:
        if (activePlayer == PLAYER2) return true;
        else return false;
    default:
        break;
    }
    return false;
}

static bool gui_snooker_isRedBallPossible()
{
    if (_isControl == false) return true;
    return (numberActions == 0 || ballsTable.red > 0);
}

static bool gui_snooker_isBlackBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.black == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.pink == 0) return true;

    return false;
}

static bool gui_snooker_isPinkBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.pink == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.blue == 0) return true;

    return false;
}

static bool gui_snooker_isBlueBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.blue == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.brown == 0) return true;

    return false;
}

static bool gui_snooker_isBrownBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.brown == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.green == 0) return true;

    return false;
}

static bool gui_snooker_isGreenBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.green == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.yellow == 0) return true;

    return false;
}

static bool gui_snooker_isYellowBallPossible()
{
    if (_isControl == false) return true;
    if (numberActions == 0 || ballsTable.yellow == 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
    case P1_F_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
    case P2_F_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    if (ballsTable.red == 0) return true;

    return false;
}

static bool gui_snooker_isLastRed()
{
    if (_isControl == false) return false;
    if (numberActions == 0 || ballsTable.red > 0) return false;

    switch (historyActions[numberActions - 1])
    {
    case P1_RED:
        if (activePlayer == PLAYER1) return true;
        break;
    case P2_RED:
        if (activePlayer == PLAYER2) return true;
        break;
    default:
        break;
    }

    return false;
}

///////////////////// SNOOKER EVENTS ////////////////////

static void ui_event_onLabelHome(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_main_create();

        _ui_screen_change(ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}

static void ui_event_onLabelReset(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_MBPanelSnookerReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_onLabelCancel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        if (numberActions > 0)
        {
            SNOOKER_ACTION removedAction = historyActions[numberActions - 1];

            numberActions--;
            ui_calculateScores();

            if (removedAction == P1_MISS || removedAction == P2_MISS || removedAction == P_FLUKE_RED) return;

            publishCurrentState();
            sendTelegaMessage(T_SNOOKER_MESSAGE_UPD, gui_snooker_getScoreMessage());
            sayFrameResult(snookerPly1Scores, snookerPly2Scores);
        }
    }
}

static void ui_event_onPlayerPanel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);

    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        // check actions overflow
        if (numberActions >= MAX_ACTIONS - 1) return;

        activePlayer = (target == ui_NPanelPly1) ? PLAYER1 : PLAYER2;

        if (gui_snooker_isFreeBallPossible())
        {
            lv_obj_clear_state(ui_BButtonFreeBall, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonFreeBall, LV_STATE_DISABLED);
        }

        if (gui_snooker_isRedBallPossible())
        {
            lv_obj_clear_state(ui_BButtonRed, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonRedF, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonF1, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonRed, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonRedF, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonF1, LV_STATE_DISABLED);
        }

        if (gui_snooker_isYellowBallPossible())
        {
            lv_obj_clear_state(ui_BButtonYellow, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonYellowF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonYellow, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonYellowF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isGreenBallPossible())
        {
            lv_obj_clear_state(ui_BButtonGreen, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonGreenF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonGreen, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonGreenF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBrownBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBrown, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonBrownF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBrown, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonBrownF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBlueBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBlue, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonBlueF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBlue, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonBlueF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isPinkBallPossible())
        {
            lv_obj_clear_state(ui_BButtonPink, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonPinkF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonPink, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonPinkF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBlackBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBlack, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBlack, LV_STATE_DISABLED);
        }

        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else if (event_code == LV_EVENT_LONG_PRESSED)
    {
        _ui_screen_change(ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}

static void ui_event_MB_ResetYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        numberActions = 0;
        ui_calculateScores();

        publishCurrentState();
        sendTelegaMessage(T_SNOOKER_MESSAGE_NEW, gui_snooker_getScoreMessage());
        sayFrameResult(snookerPly1Scores, snookerPly2Scores);

        _ui_flag_modify(ui_MBPanelSnookerReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_MBPanelSnookerPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_MB_ResetNo(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_MBPanelSnookerReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_MB_PoolYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_pool_create();

        _ui_screen_change(ui_ScreenPool, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}

static void ui_event_MB_PoolNo(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_MBPanelSnookerPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_ScreenSnooker(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        const char* plyName;

        plyName = lv_label_get_text(ui_SLabelNamePly1);
        lv_label_set_text(ui_NPlyLabelName1, plyName);

        plyName = lv_label_get_text(ui_SLabelNamePly2);
        lv_label_set_text(ui_NPlyLabelName2, plyName);

        _is6Red = lv_obj_has_state(ui_SSwitch6Red, LV_STATE_CHECKED);

        _isControl = lv_obj_has_state(ui_SSwitchControl, LV_STATE_CHECKED);

        ui_calculateScores();
    }
}

///////////////////// BALLS EVENTS ////////////////////

static void ui_event_BButtonFoul(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BButtonFreeBall(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BButtonCancel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BBallAction(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (ui_BButtonMiss == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_MISS : P2_MISS);
        }
        else if (ui_BButtonRed == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_RED : P2_RED);
        }
        else if (ui_BButtonBlack == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BLACK : P2_BLACK);
        }
        else if (ui_BButtonPink == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_PINK : P2_PINK);
        }
        else if (ui_BButtonBlue == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BLUE : P2_BLUE);
        }
        else if (ui_BButtonBrown == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BROWN : P2_BROWN);
        }
        else if (ui_BButtonGreen == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_GREEN : P2_GREEN);
        }
        else if (ui_BButtonYellow == target)
        {
            if (gui_snooker_isLastRed())
            {
                _ui_flag_modify(ui_MBPanelSnookerYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
                return;
            }

            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_YELLOW : P2_YELLOW);
        }
        else if (ui_BButtonRedF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_RED : P2_F_RED);
        }
        else if (ui_BButtonPinkF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_PINK : P2_F_PINK);
        }
        else if (ui_BButtonBlueF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_BLUE : P2_F_BLUE);
        }
        else if (ui_BButtonBrownF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_BROWN : P2_F_BROWN);
        }
        else if (ui_BButtonGreenF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_GREEN : P2_F_GREEN);
        }
        else if (ui_BButtonYellowF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_YELLOW : P2_F_YELLOW);
        }
        else if (ui_BButtonF4 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_4 : P2_FOUL_4);
        }
        else if (ui_BButtonF5 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_5 : P2_FOUL_5);
        }
        else if (ui_BButtonF6 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_6 : P2_FOUL_6);
        }
        else if (ui_BButtonF7 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_7 : P2_FOUL_7);
        }
        else if (ui_BButtonF1 == target)
        {
            gui_snooker_pushAction(P_FLUKE_RED);
        }

        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_MB_YellowYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_YELLOW : P2_YELLOW);

        _ui_flag_modify(ui_MBPanelSnookerYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
 
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_MB_YellowNo(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_MISS : P2_MISS);
        gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_YELLOW : P2_YELLOW);

        _ui_flag_modify(ui_MBPanelSnookerYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenSnooker_screen_init(void)
{
    ui_ScreenSnooker = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenSnooker, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenSnooker, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenSnooker, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelHome = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NLabelHome, 60);
    lv_obj_set_height(ui_NLabelHome, 50);
    lv_obj_set_x(ui_NLabelHome, -200);
    lv_obj_set_y(ui_NLabelHome, 125);
    lv_obj_set_align(ui_NLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_NLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_NLabelHome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelRefresh = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NLabelRefresh, 60);
    lv_obj_set_height(ui_NLabelRefresh, 50);
    lv_obj_set_x(ui_NLabelRefresh, 200);
    lv_obj_set_y(ui_NLabelRefresh, 125);
    lv_obj_set_align(ui_NLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelRefresh, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_NLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_NLabelRefresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestYellow = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestYellow, 30);
    lv_obj_set_height(ui_NRestYellow, 30);
    lv_obj_set_x(ui_NRestYellow, -70);
    lv_obj_set_y(ui_NRestYellow, 115);
    lv_obj_set_align(ui_NRestYellow, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestYellow, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestYellow, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestYellow, lv_color_hex(0xD2DD15), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestYellow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestGreen = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestGreen, 30);
    lv_obj_set_height(ui_NRestGreen, 30);
    lv_obj_set_x(ui_NRestGreen, -35);
    lv_obj_set_y(ui_NRestGreen, 115);
    lv_obj_set_align(ui_NRestGreen, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestGreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestGreen, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestGreen, lv_color_hex(0x208E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestGreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestBrown = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestBrown, 30);
    lv_obj_set_height(ui_NRestBrown, 30);
    lv_obj_set_x(ui_NRestBrown, 0);
    lv_obj_set_y(ui_NRestBrown, 115);
    lv_obj_set_align(ui_NRestBrown, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestBrown, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestBrown, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestBrown, lv_color_hex(0x75690A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestBrown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestBlue = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestBlue, 30);
    lv_obj_set_height(ui_NRestBlue, 30);
    lv_obj_set_x(ui_NRestBlue, 35);
    lv_obj_set_y(ui_NRestBlue, 115);
    lv_obj_set_align(ui_NRestBlue, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestBlue, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestBlue, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestBlue, lv_color_hex(0x0F00FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestBlue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestPink = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestPink, 30);
    lv_obj_set_height(ui_NRestPink, 30);
    lv_obj_set_x(ui_NRestPink, 70);
    lv_obj_set_y(ui_NRestPink, 115);
    lv_obj_set_align(ui_NRestPink, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestPink, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestPink, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestPink, lv_color_hex(0xE781DF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestPink, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestBlack = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestBlack, 30);
    lv_obj_set_height(ui_NRestBlack, 30);
    lv_obj_set_x(ui_NRestBlack, 105);
    lv_obj_set_y(ui_NRestBlack, 115);
    lv_obj_set_align(ui_NRestBlack, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestBlack, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestBlack, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestBlack, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestBlack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NRestRed = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NRestRed, 30);
    lv_obj_set_height(ui_NRestRed, 30);
    lv_obj_set_x(ui_NRestRed, -105);
    lv_obj_set_y(ui_NRestRed, 115);
    lv_obj_set_align(ui_NRestRed, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_NRestRed, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_NRestRed, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NRestRed, lv_color_hex(0xF20000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NRestRed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelRestRed = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_height(ui_NLabelRestRed, 30);
    lv_obj_set_width(ui_NLabelRestRed, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_NLabelRestRed, -140);
    lv_obj_set_y(ui_NLabelRestRed, 115);
    lv_obj_set_align(ui_NLabelRestRed, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelRestRed, "15");

    ui_NLabelRestScore = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NLabelRestScore, 45);
    lv_obj_set_height(ui_NLabelRestScore, 30);
    lv_obj_set_x(ui_NLabelRestScore, 150);
    lv_obj_set_y(ui_NLabelRestScore, 115);
    lv_obj_set_align(ui_NLabelRestScore, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelRestScore, "147");

    ui_NPanelPly1 = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NPanelPly1, 175);
    lv_obj_set_height(ui_NPanelPly1, 230);
    lv_obj_set_x(ui_NPanelPly1, -130);
    lv_obj_set_y(ui_NPanelPly1, 27);
    lv_obj_set_align(ui_NPanelPly1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_NPanelPly1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_NPanelPly1, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NPanelPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NPanelPly1, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NPanelPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_NPanelPly1, lv_color_hex(0xCACACA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPanelPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPanelPly1, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelName1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelName1, lv_pct(100));
    lv_obj_set_height(ui_NPlyLabelName1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelName1, 0);
    lv_obj_set_y(ui_NPlyLabelName1, -5);
    lv_obj_set_align(ui_NPlyLabelName1, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_NPlyLabelName1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_align(ui_NPlyLabelName1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelScore1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelScore1, lv_pct(120));
    lv_obj_set_height(ui_NPlyLabelScore1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NPlyLabelScore1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_NPlyLabelScore1, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_NPlyLabelScore1, "0");
    lv_obj_set_style_text_color(ui_NPlyLabelScore1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_NPlyLabelScore1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPlyLabelScore1, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_NPlyLabelScore1, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_USER_1);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore1, 255, LV_PART_MAIN | LV_STATE_USER_1);

    ui_NPlyLabelMaxScore1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelMaxScore1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMaxScore1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMaxScore1, 0);
    lv_obj_set_y(ui_NPlyLabelMaxScore1, 10);
    lv_obj_set_align(ui_NPlyLabelMaxScore1, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_NPlyLabelMaxScore1, "147");

    ui_NPlyLabelDiff1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelDiff1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelDiff1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelDiff1, 0);
    lv_obj_set_y(ui_NPlyLabelDiff1, 10);
    lv_obj_set_align(ui_NPlyLabelDiff1, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_NPlyLabelDiff1, "0");

    ui_NPanelPlyBreak = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NPanelPlyBreak, 76);
    lv_obj_set_height(ui_NPanelPlyBreak, 187);
    lv_obj_set_x(ui_NPanelPlyBreak, 0);
    lv_obj_set_y(ui_NPanelPlyBreak, 27);
    lv_obj_set_align(ui_NPanelPlyBreak, LV_ALIGN_TOP_MID);
    lv_obj_set_scrollbar_mode(ui_NPanelPlyBreak, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_set_style_bg_color(ui_NPanelPlyBreak, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NPanelPlyBreak, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NPanelPlyBreak, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NPanelPlyBreak, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_NPanelPlyBreak, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPanelPlyBreak, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPanelPlyBreak, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelPlyBreak = lv_label_create(ui_NPanelPlyBreak);
    lv_obj_set_width(ui_NLabelPlyBreak, lv_pct(100));
    lv_obj_set_height(ui_NLabelPlyBreak, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_NLabelPlyBreak, 0);
    lv_obj_set_y(ui_NLabelPlyBreak, -20);
    lv_label_set_text(ui_NLabelPlyBreak, "=  =");
    lv_label_set_recolor(ui_NLabelPlyBreak, "true");

    ui_NPanelPly2 = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NPanelPly2, 175);
    lv_obj_set_height(ui_NPanelPly2, 230);
    lv_obj_set_x(ui_NPanelPly2, 129);
    lv_obj_set_y(ui_NPanelPly2, 27);
    lv_obj_set_align(ui_NPanelPly2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_NPanelPly2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_NPanelPly2, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NPanelPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NPanelPly2, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NPanelPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_NPanelPly2, lv_color_hex(0xCACACA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPanelPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPanelPly2, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelName2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelName2, lv_pct(100));
    lv_obj_set_height(ui_NPlyLabelName2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelName2, 0);
    lv_obj_set_y(ui_NPlyLabelName2, -5);
    lv_obj_set_align(ui_NPlyLabelName2, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_NPlyLabelName2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_align(ui_NPlyLabelName2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelScore2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelScore2, lv_pct(120));
    lv_obj_set_height(ui_NPlyLabelScore2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NPlyLabelScore2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_NPlyLabelScore2, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_NPlyLabelScore2, "0");
    lv_obj_set_style_text_color(ui_NPlyLabelScore2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_NPlyLabelScore2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPlyLabelScore2, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_NPlyLabelScore2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_USER_1);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore2, 255, LV_PART_MAIN | LV_STATE_USER_1);

    ui_NPlyLabelMaxScore2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelMaxScore2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMaxScore2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMaxScore2, 0);
    lv_obj_set_y(ui_NPlyLabelMaxScore2, 10);
    lv_obj_set_align(ui_NPlyLabelMaxScore2, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_NPlyLabelMaxScore2, "147");

    ui_NPlyLabelDiff2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelDiff2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelDiff2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelDiff2, 0);
    lv_obj_set_y(ui_NPlyLabelDiff2, 10);
    lv_obj_set_align(ui_NPlyLabelDiff2, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_NPlyLabelDiff2, "0");

    ui_NButtonCancel = lv_btn_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NButtonCancel, 76);
    lv_obj_set_height(ui_NButtonCancel, 40);
    lv_obj_set_x(ui_NButtonCancel, 0);
    lv_obj_set_y(ui_NButtonCancel, 76);
    lv_obj_set_align(ui_NButtonCancel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_NButtonCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_NButtonCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_NButtonCancel, lv_color_hex(0x305814), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NButtonCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NButtonCancel, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NButtonCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NButtonCancel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelCancel = lv_label_create(ui_NButtonCancel);
    lv_obj_set_width(ui_NLabelCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NLabelCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NLabelCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelCancel, LV_SYMBOL_TRASH);
    lv_obj_clear_flag(ui_NLabelCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_MBPanelSnookerReset = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_MBPanelSnookerReset, 430);
    lv_obj_set_height(ui_MBPanelSnookerReset, 225);
    lv_obj_set_x(ui_MBPanelSnookerReset, 0);
    lv_obj_set_y(ui_MBPanelSnookerReset, 30);
    lv_obj_set_align(ui_MBPanelSnookerReset, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_MBPanelSnookerReset, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_MBPanelSnookerReset, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBPanelSnookerReset, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBPanelSnookerReset, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MBPanelSnookerReset, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MBPanelSnookerReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerResetQ = lv_label_create(ui_MBPanelSnookerReset);
    lv_obj_set_width(ui_MBLabelSnookerResetQ, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerResetQ, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MBLabelSnookerResetQ, 0);
    lv_obj_set_y(ui_MBLabelSnookerResetQ, 35);
    lv_obj_set_align(ui_MBLabelSnookerResetQ, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_MBLabelSnookerResetQ, "Начать новую партию?");
    lv_obj_set_style_text_color(ui_MBLabelSnookerResetQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MBLabelSnookerResetQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBBtnSnookerResetYes = lv_btn_create(ui_MBPanelSnookerReset);
    lv_obj_set_width(ui_MBBtnSnookerResetYes, 165);
    lv_obj_set_height(ui_MBBtnSnookerResetYes, 65);
    lv_obj_set_x(ui_MBBtnSnookerResetYes, -110);
    lv_obj_set_y(ui_MBBtnSnookerResetYes, 60);
    lv_obj_set_align(ui_MBBtnSnookerResetYes, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerResetYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerResetYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerResetYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerResetYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerResetYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerResetYes = lv_label_create(ui_MBBtnSnookerResetYes);
    lv_obj_set_width(ui_MBLabelSnookerResetYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerResetYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerResetYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerResetYes, "ДА");

    ui_MBBtnSnookerResetNo = lv_btn_create(ui_MBPanelSnookerReset);
    lv_obj_set_width(ui_MBBtnSnookerResetNo, 165);
    lv_obj_set_height(ui_MBBtnSnookerResetNo, 65);
    lv_obj_set_x(ui_MBBtnSnookerResetNo, 110);
    lv_obj_set_y(ui_MBBtnSnookerResetNo, 60);
    lv_obj_set_align(ui_MBBtnSnookerResetNo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerResetNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerResetNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerResetNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerResetNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerResetNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerResetNo = lv_label_create(ui_MBBtnSnookerResetNo);
    lv_obj_set_width(ui_MBLabelSnookerResetNo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerResetNo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerResetNo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerResetNo, "НЕТ");

    ui_MBPanelSnookerPool = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_MBPanelSnookerPool, 430);
    lv_obj_set_height(ui_MBPanelSnookerPool, 225);
    lv_obj_set_x(ui_MBPanelSnookerPool, 0);
    lv_obj_set_y(ui_MBPanelSnookerPool, 30);
    lv_obj_set_align(ui_MBPanelSnookerPool, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_MBPanelSnookerPool, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_MBPanelSnookerPool, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBPanelSnookerPool, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBPanelSnookerPool, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MBPanelSnookerPool, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MBPanelSnookerPool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerPoolQ = lv_label_create(ui_MBPanelSnookerPool);
    lv_obj_set_width(ui_MBLabelSnookerPoolQ, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerPoolQ, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MBLabelSnookerPoolQ, 0);
    lv_obj_set_y(ui_MBLabelSnookerPoolQ, 35);
    lv_obj_set_align(ui_MBLabelSnookerPoolQ, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_MBLabelSnookerPoolQ, "Обновить счёт в матче?");
    lv_obj_set_style_text_color(ui_MBLabelSnookerPoolQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MBLabelSnookerPoolQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBBtnSnookerPoolYes = lv_btn_create(ui_MBPanelSnookerPool);
    lv_obj_set_width(ui_MBBtnSnookerPoolYes, 165);
    lv_obj_set_height(ui_MBBtnSnookerPoolYes, 65);
    lv_obj_set_x(ui_MBBtnSnookerPoolYes, -110);
    lv_obj_set_y(ui_MBBtnSnookerPoolYes, 60);
    lv_obj_set_align(ui_MBBtnSnookerPoolYes, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerPoolYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerPoolYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerPoolYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerPoolYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerPoolYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerPoolYes = lv_label_create(ui_MBBtnSnookerPoolYes);
    lv_obj_set_width(ui_MBLabelSnookerPoolYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerPoolYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerPoolYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerPoolYes, "ДА");

    ui_MBBtnSnookerPoolNo = lv_btn_create(ui_MBPanelSnookerPool);
    lv_obj_set_width(ui_MBBtnSnookerPoolNo, 165);
    lv_obj_set_height(ui_MBBtnSnookerPoolNo, 65);
    lv_obj_set_x(ui_MBBtnSnookerPoolNo, 110);
    lv_obj_set_y(ui_MBBtnSnookerPoolNo, 60);
    lv_obj_set_align(ui_MBBtnSnookerPoolNo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerPoolNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerPoolNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerPoolNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerPoolNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerPoolNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerPoolNo = lv_label_create(ui_MBBtnSnookerPoolNo);
    lv_obj_set_width(ui_MBLabelSnookerPoolNo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerPoolNo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerPoolNo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerPoolNo, "НЕТ");

}

static void ui_ScreenBalls_screen_init(void)
{
    ui_BPanelBalls = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_BPanelBalls, 430);
    lv_obj_set_height(ui_BPanelBalls, 260);
    lv_obj_set_x(ui_BPanelBalls, 0);
    lv_obj_set_y(ui_BPanelBalls, 30);
    lv_obj_set_align(ui_BPanelBalls, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_BPanelBalls, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_BPanelBalls, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelBalls, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelBalls, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelBalls, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelBalls, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonRed = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonRed, 60);
    lv_obj_set_height(ui_BButtonRed, 60);
    lv_obj_set_x(ui_BButtonRed, -160);
    lv_obj_set_y(ui_BButtonRed, -85);
    lv_obj_set_align(ui_BButtonRed, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonRed, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonRed, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonRed, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonRed, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonRed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonRed, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonRed, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel1 = lv_label_create(ui_BButtonRed);
    lv_obj_set_width(ui_BLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel1, "1");

    ui_BButtonBlack = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBlack, 60);
    lv_obj_set_height(ui_BButtonBlack, 60);
    lv_obj_set_x(ui_BButtonBlack, 55);
    lv_obj_set_y(ui_BButtonBlack, 0);
    lv_obj_set_align(ui_BButtonBlack, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlack, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlack, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlack, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlack, lv_color_hex(0x6A6A6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlack, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_BButtonBlack, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_BButtonBlack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlack, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel7 = lv_label_create(ui_BButtonBlack);
    lv_obj_set_width(ui_BLabel7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel7, "7");

    ui_BButtonPink = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonPink, 60);
    lv_obj_set_height(ui_BButtonPink, 60);
    lv_obj_set_x(ui_BButtonPink, -55);
    lv_obj_set_y(ui_BButtonPink, 0);
    lv_obj_set_align(ui_BButtonPink, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonPink, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonPink, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonPink, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonPink, lv_color_hex(0xEE89E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonPink, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonPink, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonPink, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel6 = lv_label_create(ui_BButtonPink);
    lv_obj_set_width(ui_BLabel6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel6, "6");

    ui_BButtonBlue = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBlue, 60);
    lv_obj_set_height(ui_BButtonBlue, 60);
    lv_obj_set_x(ui_BButtonBlue, -160);
    lv_obj_set_y(ui_BButtonBlue, 0);
    lv_obj_set_align(ui_BButtonBlue, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlue, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlue, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlue, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlue, lv_color_hex(0x0800FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlue, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlue, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel5 = lv_label_create(ui_BButtonBlue);
    lv_obj_set_width(ui_BLabel5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel5, "5");

    ui_BButtonBrown = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBrown, 60);
    lv_obj_set_height(ui_BButtonBrown, 60);
    lv_obj_set_x(ui_BButtonBrown, 160);
    lv_obj_set_y(ui_BButtonBrown, -85);
    lv_obj_set_align(ui_BButtonBrown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBrown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBrown, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBrown, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBrown, lv_color_hex(0xA09200), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBrown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBrown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBrown, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel4 = lv_label_create(ui_BButtonBrown);
    lv_obj_set_width(ui_BLabel4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel4, "4");

    ui_BButtonGreen = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonGreen, 60);
    lv_obj_set_height(ui_BButtonGreen, 60);
    lv_obj_set_x(ui_BButtonGreen, 55);
    lv_obj_set_y(ui_BButtonGreen, -85);
    lv_obj_set_align(ui_BButtonGreen, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonGreen, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonGreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonGreen, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonGreen, lv_color_hex(0x3AFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonGreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonGreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonGreen, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel3 = lv_label_create(ui_BButtonGreen);
    lv_obj_set_width(ui_BLabel3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel3, "3");

    ui_BButtonYellow = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonYellow, 60);
    lv_obj_set_height(ui_BButtonYellow, 60);
    lv_obj_set_x(ui_BButtonYellow, -55);
    lv_obj_set_y(ui_BButtonYellow, -85);
    lv_obj_set_align(ui_BButtonYellow, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonYellow, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonYellow, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonYellow, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonYellow, lv_color_hex(0xF4FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonYellow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonYellow, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonYellow, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel2 = lv_label_create(ui_BButtonYellow);
    lv_obj_set_width(ui_BLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel2, "2");

    ui_BButtonMiss = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonMiss, 60);
    lv_obj_set_height(ui_BButtonMiss, 60);
    lv_obj_set_x(ui_BButtonMiss, 160);
    lv_obj_set_y(ui_BButtonMiss, 0);
    lv_obj_set_align(ui_BButtonMiss, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonMiss, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonMiss, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonMiss, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonMiss, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonMiss, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonMiss, lv_color_hex(0x848484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonMiss, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel0 = lv_label_create(ui_BButtonMiss);
    lv_obj_set_width(ui_BLabel0, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel0, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel0, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel0, "#000000 0#");
    lv_label_set_recolor(ui_BLabel0, "true");

    ui_BButtonFoul = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonFoul, 100);
    lv_obj_set_height(ui_BButtonFoul, 65);
    lv_obj_set_x(ui_BButtonFoul, 35);
    lv_obj_set_y(ui_BButtonFoul, 85);
    lv_obj_set_align(ui_BButtonFoul, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonFoul, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonFoul, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonFoul, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonFoul, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFoul = lv_label_create(ui_BButtonFoul);
    lv_obj_set_width(ui_BLabelFoul, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFoul, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFoul, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFoul, "Фол");

    ui_BButtonFreeBall = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonFreeBall, 165);
    lv_obj_set_height(ui_BButtonFreeBall, 65);
    lv_obj_set_x(ui_BButtonFreeBall, -110);
    lv_obj_set_y(ui_BButtonFreeBall, 85);
    lv_obj_set_align(ui_BButtonFreeBall, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonFreeBall, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonFreeBall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonFreeBall, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonFreeBall, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonFreeBall, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFreeBall = lv_label_create(ui_BButtonFreeBall);
    lv_obj_set_width(ui_BLabelFreeBall, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFreeBall, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFreeBall, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFreeBall, "Свободный\nшар");

    ui_BButtonCancel = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonCancel, 110);
    lv_obj_set_height(ui_BButtonCancel, 65);
    lv_obj_set_x(ui_BButtonCancel, 150);
    lv_obj_set_y(ui_BButtonCancel, 85);
    lv_obj_set_align(ui_BButtonCancel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonCancel, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonCancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelCancel = lv_label_create(ui_BButtonCancel);
    lv_obj_set_width(ui_BLabelCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelCancel, "Отмена");

    ui_BPanelFree = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_BPanelFree, 400);
    lv_obj_set_height(ui_BPanelFree, 160);
    lv_obj_set_x(ui_BPanelFree, 0);
    lv_obj_set_y(ui_BPanelFree, -40);
    lv_obj_set_align(ui_BPanelFree, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_BPanelFree, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelFree, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelFree, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonRedF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonRedF, 60);
    lv_obj_set_height(ui_BButtonRedF, 60);
    lv_obj_set_x(ui_BButtonRedF, -120);
    lv_obj_set_y(ui_BButtonRedF, -40);
    lv_obj_set_align(ui_BButtonRedF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonRedF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonRedF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonRedF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonRedF, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonRedF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonRedF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonRedF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB1 = lv_label_create(ui_BButtonRedF);
    lv_obj_set_width(ui_BLabelFB1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB1, "1");

    ui_BButtonYellowF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonYellowF, 60);
    lv_obj_set_height(ui_BButtonYellowF, 60);
    lv_obj_set_x(ui_BButtonYellowF, 0);
    lv_obj_set_y(ui_BButtonYellowF, -40);
    lv_obj_set_align(ui_BButtonYellowF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonYellowF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonYellowF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonYellowF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonYellowF, lv_color_hex(0xF4FC63), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonYellowF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonYellowF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonYellowF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB2 = lv_label_create(ui_BButtonYellowF);
    lv_obj_set_width(ui_BLabelFB2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB2, "2");

    ui_BButtonGreenF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonGreenF, 60);
    lv_obj_set_height(ui_BButtonGreenF, 60);
    lv_obj_set_x(ui_BButtonGreenF, 120);
    lv_obj_set_y(ui_BButtonGreenF, -40);
    lv_obj_set_align(ui_BButtonGreenF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonGreenF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonGreenF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonGreenF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonGreenF, lv_color_hex(0x3AFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonGreenF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonGreenF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonGreenF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB3 = lv_label_create(ui_BButtonGreenF);
    lv_obj_set_width(ui_BLabelFB3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB3, "3");

    ui_BButtonBrownF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonBrownF, 60);
    lv_obj_set_height(ui_BButtonBrownF, 60);
    lv_obj_set_x(ui_BButtonBrownF, -120);
    lv_obj_set_y(ui_BButtonBrownF, 40);
    lv_obj_set_align(ui_BButtonBrownF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBrownF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBrownF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBrownF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBrownF, lv_color_hex(0x736902), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBrownF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBrownF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBrownF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB4 = lv_label_create(ui_BButtonBrownF);
    lv_obj_set_width(ui_BLabelFB4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB4, "4");

    ui_BButtonBlueF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonBlueF, 60);
    lv_obj_set_height(ui_BButtonBlueF, 60);
    lv_obj_set_x(ui_BButtonBlueF, 0);
    lv_obj_set_y(ui_BButtonBlueF, 40);
    lv_obj_set_align(ui_BButtonBlueF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlueF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlueF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlueF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlueF, lv_color_hex(0x0800FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlueF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlueF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlueF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB5 = lv_label_create(ui_BButtonBlueF);
    lv_obj_set_width(ui_BLabelFB5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB5, "5");

    ui_BButtonPinkF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonPinkF, 60);
    lv_obj_set_height(ui_BButtonPinkF, 60);
    lv_obj_set_x(ui_BButtonPinkF, 120);
    lv_obj_set_y(ui_BButtonPinkF, 40);
    lv_obj_set_align(ui_BButtonPinkF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonPinkF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonPinkF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonPinkF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonPinkF, lv_color_hex(0xEE89E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonPinkF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonPinkF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonPinkF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB6 = lv_label_create(ui_BButtonPinkF);
    lv_obj_set_width(ui_BLabelFB6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB6, "6");

    ui_BPanelFoul = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_BPanelFoul, 400);
    lv_obj_set_height(ui_BPanelFoul, 160);
    lv_obj_set_x(ui_BPanelFoul, 0);
    lv_obj_set_y(ui_BPanelFoul, -40);
    lv_obj_set_align(ui_BPanelFoul, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_BPanelFoul, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelFoul, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelFoul, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonF4 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF4, 100);
    lv_obj_set_height(ui_BButtonF4, 50);
    lv_obj_set_x(ui_BButtonF4, -130);
    lv_obj_set_y(ui_BButtonF4, -35);
    lv_obj_set_align(ui_BButtonF4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF4, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF4 = lv_label_create(ui_BButtonF4);
    lv_obj_set_width(ui_BLabelF4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF4, "+4");

    ui_BButtonF5 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF5, 100);
    lv_obj_set_height(ui_BButtonF5, 50);
    lv_obj_set_x(ui_BButtonF5, 0);
    lv_obj_set_y(ui_BButtonF5, -35);
    lv_obj_set_align(ui_BButtonF5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF5, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF5 = lv_label_create(ui_BButtonF5);
    lv_obj_set_width(ui_BLabelF5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF5, "+5");

    ui_BButtonF6 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF6, 100);
    lv_obj_set_height(ui_BButtonF6, 50);
    lv_obj_set_x(ui_BButtonF6, 130);
    lv_obj_set_y(ui_BButtonF6, -35);
    lv_obj_set_align(ui_BButtonF6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF6, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF6 = lv_label_create(ui_BButtonF6);
    lv_obj_set_width(ui_BLabelF6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF6, "+6");

    ui_BButtonF7 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF7, 100);
    lv_obj_set_height(ui_BButtonF7, 50);
    lv_obj_set_x(ui_BButtonF7, -130);
    lv_obj_set_y(ui_BButtonF7, 35);
    lv_obj_set_align(ui_BButtonF7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF7, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF7 = lv_label_create(ui_BButtonF7);
    lv_obj_set_width(ui_BLabelF7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF7, "+7");

    ui_BButtonF1 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF1, 230);
    lv_obj_set_height(ui_BButtonF1, 50);
    lv_obj_set_x(ui_BButtonF1, 65);
    lv_obj_set_y(ui_BButtonF1, 35);
    lv_obj_set_align(ui_BButtonF1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF1, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF1 = lv_label_create(ui_BButtonF1);
    lv_obj_set_width(ui_BLabelF1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF1, "Упал красный");


    ui_MBPanelSnookerYellow = lv_obj_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_MBPanelSnookerYellow, 430);
    lv_obj_set_height(ui_MBPanelSnookerYellow, 260);
    lv_obj_set_x(ui_MBPanelSnookerYellow, 0);
    lv_obj_set_y(ui_MBPanelSnookerYellow, 30);
    lv_obj_add_flag(ui_MBPanelSnookerYellow, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_set_align(ui_MBPanelSnookerYellow, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_MBPanelSnookerYellow, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBPanelSnookerYellow, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBPanelSnookerYellow, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MBPanelSnookerYellow, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MBPanelSnookerYellow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerYellowQ = lv_label_create(ui_MBPanelSnookerYellow);
    lv_obj_set_width(ui_MBLabelSnookerYellowQ, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerYellowQ, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MBLabelSnookerYellowQ, 0);
    lv_obj_set_y(ui_MBLabelSnookerYellowQ, 35);
    lv_obj_set_align(ui_MBLabelSnookerYellowQ, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_MBLabelSnookerYellowQ, "Восстановить жёлтый шар?");
    lv_obj_set_style_text_color(ui_MBLabelSnookerYellowQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MBLabelSnookerYellowQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBBtnSnookerYellowYes = lv_btn_create(ui_MBPanelSnookerYellow);
    lv_obj_set_width(ui_MBBtnSnookerYellowYes, 165);
    lv_obj_set_height(ui_MBBtnSnookerYellowYes, 65);
    lv_obj_set_x(ui_MBBtnSnookerYellowYes, -110);
    lv_obj_set_y(ui_MBBtnSnookerYellowYes, 60);
    lv_obj_set_align(ui_MBBtnSnookerYellowYes, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerYellowYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerYellowYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerYellowYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerYellowYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerYellowYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerYellowYes = lv_label_create(ui_MBBtnSnookerYellowYes);
    lv_obj_set_width(ui_MBLabelSnookerYellowYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerYellowYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerYellowYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerYellowYes, "ДА");

    ui_MBBtnSnookerYellowNo = lv_btn_create(ui_MBPanelSnookerYellow);
    lv_obj_set_width(ui_MBBtnSnookerYellowNo, 165);
    lv_obj_set_height(ui_MBBtnSnookerYellowNo, 65);
    lv_obj_set_x(ui_MBBtnSnookerYellowNo, 110);
    lv_obj_set_y(ui_MBBtnSnookerYellowNo, 60);
    lv_obj_set_align(ui_MBBtnSnookerYellowNo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBBtnSnookerYellowNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBBtnSnookerYellowNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBBtnSnookerYellowNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBBtnSnookerYellowNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MBBtnSnookerYellowNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBLabelSnookerYellowNo = lv_label_create(ui_MBBtnSnookerYellowNo);
    lv_obj_set_width(ui_MBLabelSnookerYellowNo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBLabelSnookerYellowNo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBLabelSnookerYellowNo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBLabelSnookerYellowNo, "НЕТ");

}

///////////////////// EXPORT ////////////////////

void gui_snooker_create()
{
    ui_ScreenSnooker_screen_init();

    lv_obj_add_event_cb(ui_ScreenSnooker, ui_event_ScreenSnooker, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_NLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NLabelRefresh, ui_event_onLabelReset, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_NPanelPly1, ui_event_onPlayerPanel, LV_EVENT_ALL, ui_NPlyLabelName1);
    lv_obj_add_event_cb(ui_NPanelPly2, ui_event_onPlayerPanel, LV_EVENT_ALL, ui_NPlyLabelName2);

    lv_obj_add_event_cb(ui_NButtonCancel, ui_event_onLabelCancel, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_MBBtnSnookerResetYes, ui_event_MB_ResetYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBBtnSnookerResetNo, ui_event_MB_ResetNo, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBBtnSnookerPoolYes, ui_event_MB_PoolYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBBtnSnookerPoolNo, ui_event_MB_PoolNo, LV_EVENT_ALL, NULL);

    ui_ScreenBalls_screen_init();

    lv_obj_add_event_cb(ui_BButtonFoul, ui_event_BButtonFoul, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonFreeBall, ui_event_BButtonFreeBall, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonCancel, ui_event_BButtonCancel, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_BButtonMiss, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonRed, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlack, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonPink, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlue, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBrown, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonGreen, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonYellow, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonRedF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonPinkF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlueF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBrownF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonGreenF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonYellowF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF4, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF5, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF6, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF7, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF1, ui_event_BBallAction, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_MBBtnSnookerYellowYes, ui_event_MB_YellowYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBBtnSnookerYellowNo, ui_event_MB_YellowNo, LV_EVENT_ALL, NULL);

}

void gui_snooker_delete()
{
    if (ui_ScreenSnooker == NULL) return;

    lv_obj_del(ui_ScreenSnooker);
    ui_ScreenSnooker = NULL;
}

String gui_snooker_getScoreMessage()
{
    String msg = F("СНУКЕР:\n");

    msg += lv_label_get_text(ui_NPlyLabelScore1);
    msg += F(" - ");
    msg += lv_label_get_text(ui_NPlyLabelName1);

    msg += F("\n");

    msg += lv_label_get_text(ui_NPlyLabelScore2);
    msg += F(" - ");
    msg += lv_label_get_text(ui_NPlyLabelName2);

    return msg;
}


