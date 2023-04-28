#include "gui_snooker.h"
#include "gui_balls.h"
#include "gui_main.h"
#include "gui_components.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

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
lv_obj_t* ui_NPanelPly1;
lv_obj_t* ui_NPlyLabelName1;
lv_obj_t* ui_NPlyLabelScore1;
lv_obj_t* ui_NPlyLabelMaxScore1;
lv_obj_t* ui_NPlyLabelMax1;
lv_obj_t* ui_NPanelPlyBreak;
lv_obj_t* ui_NLabelPlyBreak;
lv_obj_t* ui_NPanelPly2;
lv_obj_t* ui_NPlyLabelName2;
lv_obj_t* ui_NPlyLabelScore2;
lv_obj_t* ui_NPlyLabelMaxScore2;
lv_obj_t* ui_NPlyLabelMax2;
lv_obj_t* ui_NButtonCancel;
lv_obj_t* ui_NLabelCancel;
lv_obj_t* ui_NNameKeyboard;

static lv_timer_t* telegramTimer;

static bool publishScore = false;
static int32_t lastMsgId = -1;

extern int32_t sendMessageToChannel(String& msg, int32_t msgId = -1);

#define COLOR_RED "F20000"
#define COLOR_BLACK "000000"
#define COLOR_PINK "E781DF"
#define COLOR_BLUE "0F00FF"
#define COLOR_BROWN "75690A"
#define COLOR_GREEN "208E02"
#define COLOR_YELLOW "D2DD15"

#define MAX_ACTIONS 1024						// maximum amount of actions

SNOOKER_ACTION historyActions[MAX_ACTIONS];		// list of actions

uint16_t numberActions = 0;						// number of executed actions

SNOOKER_PLAYER activePlayer;					// player who made last action

struct BALLS
{
    uint8_t red;
    uint8_t black;
    uint8_t pink;
    uint8_t blue;
    uint8_t brown;
    uint8_t green;
    uint8_t yellow;
}
ballsTable;

uint16_t _handicapP1 = 0;
uint16_t _handicapP2 = 0;
bool _is6Red = false;

///////////////////// FUNCTIONS ////////////////////

static void sendScore(lv_timer_t* timer)
{
    if (publishScore)
    {
        publishScore = false;

        String msg = F("СНУКЕР:\n");

        msg += lv_label_get_text(ui_NPlyLabelScore1);
        msg += F(" - ");
        msg += lv_label_get_text(ui_NPlyLabelName1);

        msg += F("\n");

        msg += lv_label_get_text(ui_NPlyLabelScore2);
        msg += F(" - ");
        msg += lv_label_get_text(ui_NPlyLabelName2);

        lastMsgId = sendMessageToChannel(msg, lastMsgId);
    }
}

static void calculateScores()
{
    String plySeries = "=  =\n";

    uint16_t ply1Scores = _handicapP1;
    uint16_t ply2Scores = _handicapP2;

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
    
    // Calculate scores
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
            ply1Scores += 1;
            plySeries += "#" COLOR_RED " 1#\n";
            break;
        case P1_BLACK:
            if (ballsTable.pink == 0) ballsTable.black--;
            ply1Scores += 7;
            plySeries += "#" COLOR_BLACK " 7#\n";
            break;
        case P1_PINK:
            if (ballsTable.blue == 0) ballsTable.pink--;
            ply1Scores += 6;
            plySeries += "#" COLOR_PINK " 6#\n";
            break;
        case P1_BLUE:
            if (ballsTable.brown == 0) ballsTable.blue--;
            ply1Scores += 5;
            plySeries += "#" COLOR_BLUE " 5#\n";
            break;
        case P1_BROWN:
            if (ballsTable.green == 0) ballsTable.brown--;
            ply1Scores += 4;
            plySeries += "#" COLOR_BROWN " 4#\n";
            break;
        case P1_GREEN:
            if (ballsTable.yellow == 0) ballsTable.green--;
            ply1Scores += 3;
            plySeries += "#" COLOR_GREEN " 3#\n";
            break;
        case P1_YELLOW:
            if (ballsTable.red == 0) ballsTable.yellow--;
            ply1Scores += 2;
            plySeries += "#" COLOR_YELLOW " 2#\n";
            break;
        case P1_F_RED:
            ply1Scores += 1;
            plySeries += "#" COLOR_RED " 1.#\n";
            break;
        case P1_F_PINK:
            ply1Scores += 6;
            plySeries += "#" COLOR_PINK " 6.#\n";
            break;
        case P1_F_BLUE:
            ply1Scores += 5;
            plySeries += "#" COLOR_BLUE " 5.#\n";
            break;
        case P1_F_BROWN:
            ply1Scores += 4;
            plySeries += "#" COLOR_BROWN " 4.#\n";
            break;
        case P1_F_GREEN:
            ply1Scores += 3;
            plySeries += "#" COLOR_GREEN " 3.#\n";
            break;
        case P1_F_YELLOW:
            ply1Scores += 2;
            plySeries += "#" COLOR_YELLOW " 2.#\n";
            break;
        case P1_FOUL_4:
            ply1Scores += 4;
            plySeries += "4+\n";
            break;
        case P1_FOUL_5:
            ply1Scores += 5;
            plySeries += "5+\n";
            break;
        case P1_FOUL_6:
            ply1Scores += 6;
            plySeries += "6+\n";
            break;
        case P1_FOUL_7:
            ply1Scores += 7;
            plySeries += "7+\n";
            break;
            // PLAYER2
        case P2_MISS:
            plySeries += "     -\n";
            break;
        case P2_RED:
            ballsTable.red--;
            ply2Scores += 1;
            plySeries += "#" COLOR_RED "     1#\n";
            break;
        case P2_BLACK:
            if (ballsTable.pink == 0) ballsTable.black--;
            ply2Scores += 7;
            plySeries += "#" COLOR_BLACK "     7#\n";
            break;
        case P2_PINK:
            if (ballsTable.blue == 0) ballsTable.pink--;
            ply2Scores += 6;
            plySeries += "#" COLOR_PINK "     6#\n";
            break;
        case P2_BLUE:
            if (ballsTable.brown == 0) ballsTable.blue--;
            ply2Scores += 5;
            plySeries += "#" COLOR_BLUE "     5#\n";
            break;
        case P2_BROWN:
            if (ballsTable.green == 0) ballsTable.brown--;
            ply2Scores += 4;
            plySeries += "#" COLOR_BROWN "     4#\n";
            break;
        case P2_GREEN:
            if (ballsTable.yellow == 0) ballsTable.green--;
            ply2Scores += 3;
            plySeries += "#" COLOR_GREEN "     3#\n";
            break;
        case P2_YELLOW:
            if (ballsTable.red == 0) ballsTable.yellow--;
            ply2Scores += 2;
            plySeries += "#" COLOR_YELLOW "     2#\n";
            break;
        case P2_F_RED:
            ply2Scores += 1;
            plySeries += "#" COLOR_RED "    .1#\n";
            break;
        case P2_F_PINK:
            ply2Scores += 6;
            plySeries += "#" COLOR_PINK "    .6#\n";
            break;
        case P2_F_BLUE:
            ply2Scores += 5;
            plySeries += "#" COLOR_BLUE "    .5#\n";
            break;
        case P2_F_BROWN:
            ply2Scores += 4;
            plySeries += "#" COLOR_BROWN "    .4#\n";
            break;
        case P2_F_GREEN:
            ply2Scores += 3;
            plySeries += "#" COLOR_GREEN "    .3#\n";
            break;
        case P2_F_YELLOW:
            ply2Scores += 2;
            plySeries += "#" COLOR_YELLOW "    .2#\n";
            break;
        case P2_FOUL_4:
            ply2Scores += 4;
            plySeries += "  +4\n";
            break;
        case P2_FOUL_5:
            ply2Scores += 5;
            plySeries += "  +5\n";
            break;
        case P2_FOUL_6:
            ply2Scores += 6;
            plySeries += "  +6\n";
            break;
        case P2_FOUL_7:
            ply2Scores += 7;
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

    lv_label_set_text_fmt(ui_NPlyLabelScore1, "%d", ply1Scores);
    lv_label_set_text_fmt(ui_NPlyLabelScore2, "%d", ply2Scores);

    // Calculate max series
    uint8_t scoresOnTable = 8 * ballsTable.red + 7 * ballsTable.black + 6 * ballsTable.pink + 5 * ballsTable.blue + 4 * ballsTable.brown + 3 * ballsTable.green + 2 * ballsTable.yellow;

    uint16_t ply1Max = ply1Scores + scoresOnTable;
    uint16_t ply2Max = ply2Scores + scoresOnTable;

    if (numberActions > 0)
    {
        if (historyActions[numberActions - 1] == P1_RED || historyActions[numberActions - 1] == P1_F_RED)
            ply1Max += 7;
        if (historyActions[numberActions - 1] == P2_RED || historyActions[numberActions - 1] == P2_F_RED)
            ply2Max += 7;
    }

    lv_label_set_text_fmt(ui_NPlyLabelMaxScore1, "%d", ply1Max);
    lv_label_set_text_fmt(ui_NPlyLabelMaxScore2, "%d", ply2Max);

    // Show series
    lv_label_set_text(ui_NLabelPlyBreak, plySeries.c_str());
    lv_obj_scroll_to_y(ui_NPanelPlyBreak, lv_obj_get_height(ui_NLabelPlyBreak), LV_ANIM_OFF);

    // Show available balls
    if (ballsTable.red > 0)
    {
        lv_label_set_text_fmt(ui_NLabelRestRed, "%d", ballsTable.red);
        _ui_flag_modify(ui_NRestRed, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        lv_label_set_text(ui_NLabelRestRed, "");
        _ui_flag_modify(ui_NRestRed, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.black > 0)
    {
        _ui_flag_modify(ui_NRestBlack, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestBlack, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.pink > 0)
    {
        _ui_flag_modify(ui_NRestPink, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestPink, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.blue > 0)
    {
        _ui_flag_modify(ui_NRestBlue, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestBlue, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.brown > 0)
    {
        _ui_flag_modify(ui_NRestBrown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestBrown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.green > 0)
    {
        _ui_flag_modify(ui_NRestGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (ballsTable.yellow > 0)
    {
        _ui_flag_modify(ui_NRestYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    else
    {
        _ui_flag_modify(ui_NRestYellow, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_ScreenSnooker(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        calculateScores();
    }
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        lv_timer_resume(telegramTimer);
    }
    else if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
    {
        lv_timer_pause(telegramTimer);
    }
}

static void ui_event_onLabelHome(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}

static void ui_event_onLabelRefresh(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        numberActions = 0;
        calculateScores();
        publishScore = true;
        lastMsgId = -1; // publish as a new message
    }
}

static void ui_event_onLabelCancel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (numberActions > 0)
        {
            if (historyActions[numberActions - 1] != P1_MISS && historyActions[numberActions - 1] != P2_MISS && historyActions[numberActions - 1] != P_FLUKE_RED)
                publishScore = true;

            numberActions--;
            calculateScores();
        }
    }
}

static void ui_event_onPlayerPanel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t* lb = static_cast<lv_obj_t*>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED && lv_obj_has_flag(ui_NNameKeyboard, LV_OBJ_FLAG_HIDDEN))
    {
        // check actions overflow
        if (numberActions >= MAX_ACTIONS - 1) return;

        activePlayer = (target == ui_NPanelPly1) ? PLAYER1 : PLAYER2;

        _ui_screen_change(ui_ScreenBalls, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
    else if (event_code == LV_EVENT_LONG_PRESSED)
    {
        ui_comp_set_child(ui_NNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMELABEL, lb);

        lv_textarea_set_text(ui_comp_get_child(ui_NNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), lv_label_get_text(lb));

        _ui_flag_modify(ui_NNameKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

///////////////////// SCREENS ////////////////////

void ui_ScreenSnooker_screen_init(void)
{
    ui_ScreenSnooker = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenSnooker, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenSnooker, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenSnooker, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NLabelHome = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NLabelHome, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NLabelHome, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NLabelHome, -200);
    lv_obj_set_y(ui_NLabelHome, 115);
    lv_obj_set_align(ui_NLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_NLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_NLabelRefresh = lv_label_create(ui_ScreenSnooker);
    lv_obj_set_width(ui_NLabelRefresh, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NLabelRefresh, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NLabelRefresh, 200);
    lv_obj_set_y(ui_NLabelRefresh, 115);
    lv_obj_set_align(ui_NLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NLabelRefresh, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_NLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags

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
    lv_label_set_text(ui_NPlyLabelName1, "Игрок 1");
    lv_obj_set_style_text_align(ui_NPlyLabelName1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelScore1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelScore1, lv_pct(120));
    lv_obj_set_height(ui_NPlyLabelScore1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NPlyLabelScore1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_NPlyLabelScore1, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_NPlyLabelScore1, "147");
    lv_obj_set_style_text_color(ui_NPlyLabelScore1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_NPlyLabelScore1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPlyLabelScore1, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelMaxScore1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelMaxScore1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMaxScore1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMaxScore1, 0);
    lv_obj_set_y(ui_NPlyLabelMaxScore1, 10);
    lv_obj_set_align(ui_NPlyLabelMaxScore1, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_NPlyLabelMaxScore1, "147");

    ui_NPlyLabelMax1 = lv_label_create(ui_NPanelPly1);
    lv_obj_set_width(ui_NPlyLabelMax1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMax1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMax1, 0);
    lv_obj_set_y(ui_NPlyLabelMax1, 10);
    lv_obj_set_align(ui_NPlyLabelMax1, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_NPlyLabelMax1, "max >");

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
    lv_label_set_text(ui_NLabelPlyBreak, "=  =\n");
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
    lv_label_set_text(ui_NPlyLabelName2, "Игрок 2");
    lv_obj_set_style_text_align(ui_NPlyLabelName2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelScore2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelScore2, lv_pct(120));
    lv_obj_set_height(ui_NPlyLabelScore2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NPlyLabelScore2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_NPlyLabelScore2, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_NPlyLabelScore2, "147");
    lv_obj_set_style_text_color(ui_NPlyLabelScore2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NPlyLabelScore2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_NPlyLabelScore2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NPlyLabelScore2, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NPlyLabelMaxScore2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelMaxScore2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMaxScore2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMaxScore2, 0);
    lv_obj_set_y(ui_NPlyLabelMaxScore2, 10);
    lv_obj_set_align(ui_NPlyLabelMaxScore2, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_NPlyLabelMaxScore2, "147");

    ui_NPlyLabelMax2 = lv_label_create(ui_NPanelPly2);
    lv_obj_set_width(ui_NPlyLabelMax2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NPlyLabelMax2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_NPlyLabelMax2, 0);
    lv_obj_set_y(ui_NPlyLabelMax2, 10);
    lv_obj_set_align(ui_NPlyLabelMax2, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_NPlyLabelMax2, "< max");

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

    ui_NNameKeyboard = ui_NameKeyboard_create(ui_ScreenSnooker);
    lv_obj_set_x(ui_NNameKeyboard, 0);
    lv_obj_set_y(ui_NNameKeyboard, 0);
    lv_obj_add_flag(ui_NNameKeyboard, LV_OBJ_FLAG_HIDDEN);     /// Flags

}

void gui_snooker_init()
{
    ui_ScreenSnooker_screen_init();

    lv_obj_add_event_cb(ui_ScreenSnooker, ui_event_ScreenSnooker, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NLabelRefresh, ui_event_onLabelRefresh, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NPanelPly1, ui_event_onPlayerPanel, LV_EVENT_ALL, ui_NPlyLabelName1);
    lv_obj_add_event_cb(ui_NPanelPly2, ui_event_onPlayerPanel, LV_EVENT_ALL, ui_NPlyLabelName2);
    lv_obj_add_event_cb(ui_NButtonCancel, ui_event_onLabelCancel, LV_EVENT_ALL, NULL);

    telegramTimer = lv_timer_create(sendScore, 5000, NULL);
    lv_timer_pause(telegramTimer);
}

SNOOKER_PLAYER gui_snooker_get_activePlayer()
{
    return activePlayer;
}

void gui_snooker_pushAction(SNOOKER_ACTION sAction)
{
    // Save action
    historyActions[numberActions++] = sAction;

    if (sAction != P1_MISS && sAction != P2_MISS && sAction != P_FLUKE_RED)
        publishScore = true;
}

bool gui_snooker_isFreeBallPossible()
{
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
        return false;
    }
}

bool gui_snooker_isRedBallPossible()
{
    return ballsTable.red;
}

bool gui_snooker_isBlackBallPossible()
{
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

bool gui_snooker_isPinkBallPossible()
{
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

bool gui_snooker_isBlueBallPossible()
{
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

bool gui_snooker_isBrownBallPossible()
{
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

bool gui_snooker_isGreenBallPossible()
{
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

bool gui_snooker_isYellowBallPossible()
{
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

void gui_snooker_setHandicapP1(uint16_t handicap)
{
    _handicapP1 = handicap;
}

void gui_snooker_setHandicapP2(uint16_t handicap)
{
    _handicapP2 = handicap;
}

void gui_snooker_set6Red(bool is6Red)
{
    numberActions = 0;

    lastMsgId = -1; // publish as a new message

    _is6Red = is6Red;
}
