#include "gui_darts.h"
#include "gui.h"
#include "gui_main.h"
#include "gui_settings.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

#include "darts/Dart.h"
#include <vector>

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenDarts;
lv_obj_t* ui_DPanelPlayers;
lv_obj_t* ui_DPanelPly1;
lv_obj_t* ui_DLabelPly1;
lv_obj_t* ui_DPanelPly2;
lv_obj_t* ui_DLabelPly2;
lv_obj_t* ui_DPanelPly3;
lv_obj_t* ui_DLabelPly3;
lv_obj_t* ui_DPanelGame;
lv_obj_t* ui_DLabelSuggest;
lv_obj_t* ui_DLabelScore;
lv_obj_t* ui_DPanelHistory;
lv_obj_t* ui_DLabelHistory;
lv_obj_t* ui_DButtonSector;
lv_obj_t* ui_DLabelSector;
lv_obj_t* ui_DButtonDouble;
lv_obj_t* ui_DLabelDouble;
lv_obj_t* ui_DButtonTriple;
lv_obj_t* ui_DLabelTriple;
lv_obj_t* ui_DLabelHome;
lv_obj_t* ui_DLabelReset;
lv_obj_t* ui_DLabelTrash;
lv_obj_t* ui_DPanelReset;
lv_obj_t* ui_DLabelNew;
lv_obj_t* ui_DButtonYes;
lv_obj_t* ui_DLabelYes;
lv_obj_t* ui_DButtonNo;
lv_obj_t* ui_DLabelNo;
lv_obj_t* ui_DPanelRemove;
lv_obj_t* ui_DLabelRemove;
lv_obj_t* ui_DButtonRemoveYes;
lv_obj_t* ui_DLabelRemoveYes;
lv_obj_t* ui_DButtonRemoveNo;
lv_obj_t* ui_DLabelRemoveNo;
lv_obj_t* ui_DPanelKB;
lv_obj_t* ui_DTextArea;
lv_obj_t* ui_DKeyboard;

static std::vector<Dart> dartsPly1;
static std::vector<Dart> dartsPly2;
static std::vector<Dart> dartsPly3;

static std::vector<Dart>* dartsToShow = &dartsPly1;
static DartType dartToAdd;

static const char* darts_kb_map_num[] = { "1", "2", "3", LV_SYMBOL_CLOSE, "\n",
                                                "4", "5", "6", LV_SYMBOL_BACKSPACE, "\n",
                                                "7", "8", "9", LV_SYMBOL_LEFT, LV_SYMBOL_RIGHT, "\n",
                                                "+/-", "0", LV_SYMBOL_OK, ""
};

static const lv_btnmatrix_ctrl_t darts_kb_ctrl_num_map[] = {
    1, 1, 1, LV_KEYBOARD_CTRL_BTN_FLAGS | 2,
    1, 1, 1, 2,
    1, 1, 1, 1, 1,
    1, 1, LV_KEYBOARD_CTRL_BTN_FLAGS | 3
};

///////////////////// FUNCTIONS ////////////////////

static void ui_calculate_score()
{
    int16_t scores = 501;
    String series = "501 ";

    for (auto it = dartsToShow->cbegin(); it != dartsToShow->cend(); ++it)
    {
        series += it->toString();
        series += " ";

        switch (it->getType())
        {
        case DartType::SCORES:
            if (it->getScore() >= 0) scores = it->getScore(); // the positive value means manual calculated scores
            else scores += it->getScore();                    // the negative value means the series of darts to decrease
            break;
        default:
            scores -= it->getScore();
            break;
        }
    }

    lv_label_set_text_fmt(ui_DLabelScore, "%d", scores);
    lv_label_set_text(ui_DLabelSuggest, suggest(scores).c_str());
    lv_label_set_text(ui_DLabelHistory, series.c_str());
    lv_obj_scroll_to_x(ui_DPanelHistory, lv_obj_get_width(ui_DLabelHistory), LV_ANIM_OFF);

}

///////////////////// EVENTS ////////////////////

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
        _ui_flag_modify(ui_DPanelReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_DButtonYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_DPanelReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        dartsPly1.clear();
        dartsPly2.clear();
        dartsPly3.clear();

        ui_calculate_score();
    }
}

static void ui_event_DButtonNo(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_DPanelReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_DPanelPly1(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_DPanelPly3, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_DPanelPly2, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_DPanelPly1, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);

        dartsToShow = &dartsPly1;
        ui_calculate_score();
    }
}
static void ui_event_DPanelPly2(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_DPanelPly3, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_DPanelPly2, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_DPanelPly1, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);

        dartsToShow = &dartsPly2;
        ui_calculate_score();
    }
}
static void ui_event_DPanelPly3(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_state_modify(ui_DPanelPly3, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_DPanelPly2, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_DPanelPly1, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);

        dartsToShow = &dartsPly3;
        ui_calculate_score();
    }
}

static void ui_event_DLabelScore(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        lv_textarea_set_text(ui_DTextArea, "");
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

        dartToAdd = SCORES;
    }
}

static void ui_event_DButtonSector(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        lv_textarea_set_text(ui_DTextArea, "");
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

        dartToAdd = SECTOR;
    }
}
static void ui_event_DButtonDouble(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        lv_textarea_set_text(ui_DTextArea, "");
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

        dartToAdd = DOUBLE;
    }
}
static void ui_event_DButtonTriple(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        lv_textarea_set_text(ui_DTextArea, "");
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

        dartToAdd = TRIPLE;
    }
}

static void ui_event_DLabelTrash(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_DPanelRemove, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_DButtonRemoveYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_DPanelRemove, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        if (!dartsToShow->empty())
        {
            dartsToShow->pop_back();
            ui_calculate_score();
        }
    }
}
static void ui_event_DButtonRemoveNo(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_DPanelRemove, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_DTextArea(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_READY)
    {
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        int16_t score = atoi(lv_textarea_get_text(ui_DTextArea));

        if (dartToAdd != SCORES)
        {
            if (score <= 0) return;

            if (score > 20)
            {
                if (dartToAdd == DOUBLE || dartToAdd == TRIPLE) return;

                if (score != 25 && score != 50) return;
            }
        }

        dartsToShow->push_back(Dart(dartToAdd, score));

        ui_calculate_score();
    }
    else if (event_code == LV_EVENT_CANCEL)
    {
        _ui_flag_modify(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_ScreenDarts(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        lv_label_set_text(ui_DLabelPly1, lv_label_get_text(ui_SLabelNamePly1));
        lv_label_set_text(ui_DLabelPly2, lv_label_get_text(ui_SLabelNamePly2));
        lv_label_set_text(ui_DLabelPly3, lv_label_get_text(ui_SLabelNamePly3));

        dartsToShow = &dartsPly1;
        ui_calculate_score();
    }
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenDarts_screen_init(void)
{
    ui_ScreenDarts = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenDarts, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_text_font(ui_ScreenDarts, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelPlayers = lv_obj_create(ui_ScreenDarts);
    lv_obj_set_width(ui_DPanelPlayers, lv_pct(100));
    lv_obj_set_height(ui_DPanelPlayers, lv_pct(20));
    lv_obj_set_align(ui_DPanelPlayers, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DPanelPlayers, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_DPanelPlayers, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPlayers, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_DPanelPlayers, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelPly1 = lv_obj_create(ui_DPanelPlayers);
    lv_obj_set_width(ui_DPanelPly1, 160);
    lv_obj_set_height(ui_DPanelPly1, 60);
    lv_obj_set_x(ui_DPanelPly1, -15);
    lv_obj_set_y(ui_DPanelPly1, -15);
    lv_obj_add_state(ui_DPanelPly1, LV_STATE_CHECKED);       /// States
    lv_obj_clear_flag(ui_DPanelPly1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_DPanelPly1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly1, lv_color_hex(0x656565), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DPanelPly1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_DPanelPly1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DPanelPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_DPanelPly1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(ui_DPanelPly1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui_DPanelPly1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui_DPanelPly1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_DLabelPly1 = lv_label_create(ui_DPanelPly1);
    lv_obj_set_width(ui_DLabelPly1, lv_pct(100));
    lv_obj_set_height(ui_DLabelPly1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelPly1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DLabelPly1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DLabelPly1, "1");
    lv_obj_set_style_text_align(ui_DLabelPly1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelPly2 = lv_obj_create(ui_DPanelPlayers);
    lv_obj_set_width(ui_DPanelPly2, 160);
    lv_obj_set_height(ui_DPanelPly2, 60);
    lv_obj_set_x(ui_DPanelPly2, 145);
    lv_obj_set_y(ui_DPanelPly2, -15);
    lv_obj_clear_flag(ui_DPanelPly2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_DPanelPly2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly2, lv_color_hex(0x095706), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DPanelPly2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_DPanelPly2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DPanelPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_DPanelPly2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(ui_DPanelPly2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_DLabelPly2 = lv_label_create(ui_DPanelPly2);
    lv_obj_set_width(ui_DLabelPly2, lv_pct(100));
    lv_obj_set_height(ui_DLabelPly2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelPly2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DLabelPly2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DLabelPly2, "2");
    lv_obj_set_style_text_align(ui_DLabelPly2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelPly3 = lv_obj_create(ui_DPanelPlayers);
    lv_obj_set_width(ui_DPanelPly3, 160);
    lv_obj_set_height(ui_DPanelPly3, 60);
    lv_obj_set_x(ui_DPanelPly3, 305);
    lv_obj_set_y(ui_DPanelPly3, -15);
    lv_obj_clear_flag(ui_DPanelPly3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_DPanelPly3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly3, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelPly3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DPanelPly3, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_DPanelPly3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DPanelPly3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelPly3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_DPanelPly3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(ui_DPanelPly3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_DLabelPly3 = lv_label_create(ui_DPanelPly3);
    lv_obj_set_width(ui_DLabelPly3, lv_pct(100));
    lv_obj_set_height(ui_DLabelPly3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelPly3, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DLabelPly3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DLabelPly3, "3");
    lv_obj_set_style_text_align(ui_DLabelPly3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelGame = lv_obj_create(ui_ScreenDarts);
    lv_obj_set_width(ui_DPanelGame, lv_pct(100));
    lv_obj_set_height(ui_DPanelGame, lv_pct(80));
    lv_obj_set_align(ui_DPanelGame, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_DPanelGame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_DPanelGame, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DPanelGame, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_DPanelGame, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelSuggest = lv_label_create(ui_DPanelGame);
    lv_obj_set_width(ui_DLabelSuggest, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelSuggest, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DLabelSuggest, 100);
    lv_obj_set_y(ui_DLabelSuggest, -165);
    lv_obj_set_align(ui_DLabelSuggest, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_DLabelSuggest, "");
    lv_obj_set_style_text_color(ui_DLabelSuggest, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelSuggest, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DLabelSuggest, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelScore = lv_label_create(ui_DPanelGame);
    lv_obj_set_width(ui_DLabelScore, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelScore, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DLabelScore, 40);
    lv_obj_set_y(ui_DLabelScore, 0);
    lv_label_set_text(ui_DLabelScore, "501");
    lv_obj_add_flag(ui_DLabelScore, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_DLabelScore, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DLabelScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelHistory = lv_obj_create(ui_DPanelGame);
    lv_obj_set_width(ui_DPanelHistory, 465);
    lv_obj_set_height(ui_DPanelHistory, 65);
    lv_obj_set_x(ui_DPanelHistory, 0);
    lv_obj_set_y(ui_DPanelHistory, 50);
    lv_obj_set_align(ui_DPanelHistory, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_DPanelHistory, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelHistory, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DPanelHistory, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_DPanelHistory, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DPanelHistory, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelHistory = lv_label_create(ui_DPanelHistory);
    lv_obj_set_width(ui_DLabelHistory, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelHistory, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelHistory, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_DLabelHistory, "501 ");
    lv_obj_set_style_text_align(ui_DLabelHistory, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DButtonSector = lv_btn_create(ui_DPanelGame);
    lv_obj_set_width(ui_DButtonSector, 150);
    lv_obj_set_height(ui_DButtonSector, 40);
    lv_obj_set_x(ui_DButtonSector, -155);
    lv_obj_set_y(ui_DButtonSector, 0);
    lv_obj_set_align(ui_DButtonSector, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DButtonSector, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonSector, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelSector = lv_label_create(ui_DButtonSector);
    lv_obj_set_width(ui_DLabelSector, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelSector, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelSector, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelSector, "Сектор");

    ui_DButtonDouble = lv_btn_create(ui_DPanelGame);
    lv_obj_set_width(ui_DButtonDouble, 150);
    lv_obj_set_height(ui_DButtonDouble, 40);
    lv_obj_set_align(ui_DButtonDouble, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DButtonDouble, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonDouble, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelDouble = lv_label_create(ui_DButtonDouble);
    lv_obj_set_width(ui_DLabelDouble, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelDouble, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelDouble, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelDouble, "Удвоение");

    ui_DButtonTriple = lv_btn_create(ui_DPanelGame);
    lv_obj_set_width(ui_DButtonTriple, 150);
    lv_obj_set_height(ui_DButtonTriple, 40);
    lv_obj_set_x(ui_DButtonTriple, 155);
    lv_obj_set_y(ui_DButtonTriple, 0);
    lv_obj_set_align(ui_DButtonTriple, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DButtonTriple, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonTriple, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelTriple = lv_label_create(ui_DButtonTriple);
    lv_obj_set_width(ui_DLabelTriple, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelTriple, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelTriple, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelTriple, "Утроение");

    ui_DLabelHome = lv_label_create(ui_DPanelGame);
    lv_obj_set_width(ui_DLabelHome, 60);
    lv_obj_set_height(ui_DLabelHome, 40);
    lv_obj_set_x(ui_DLabelHome, -13);
    lv_obj_set_y(ui_DLabelHome, 12);
    lv_obj_set_align(ui_DLabelHome, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_DLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_DLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_DLabelHome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DLabelHome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelReset = lv_label_create(ui_DPanelGame);
    lv_obj_set_width(ui_DLabelReset, 60);
    lv_obj_set_height(ui_DLabelReset, 40);
    lv_obj_set_x(ui_DLabelReset, 12);
    lv_obj_set_y(ui_DLabelReset, 12);
    lv_obj_set_align(ui_DLabelReset, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_DLabelReset, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_DLabelReset, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_DLabelReset, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DLabelReset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelTrash = lv_label_create(ui_DPanelGame);
    lv_obj_set_width(ui_DLabelTrash, 60);
    lv_obj_set_height(ui_DLabelTrash, 40);
    lv_obj_set_x(ui_DLabelTrash, 0);
    lv_obj_set_y(ui_DLabelTrash, 12);
    lv_obj_set_align(ui_DLabelTrash, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_DLabelTrash, LV_SYMBOL_TRASH);
    lv_obj_add_flag(ui_DLabelTrash, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_DLabelTrash, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelTrash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DLabelTrash, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DPanelReset = lv_obj_create(ui_ScreenDarts);
    lv_obj_set_width(ui_DPanelReset, lv_pct(100));
    lv_obj_set_height(ui_DPanelReset, lv_pct(100));
    lv_obj_set_align(ui_DPanelReset, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DPanelReset, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_DPanelReset, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_DPanelReset, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelNew = lv_label_create(ui_DPanelReset);
    lv_obj_set_width(ui_DLabelNew, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelNew, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DLabelNew, -1);
    lv_obj_set_y(ui_DLabelNew, 80);
    lv_obj_set_align(ui_DLabelNew, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DLabelNew, "Начать новую игру?");
    lv_obj_set_style_text_color(ui_DLabelNew, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelNew, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DButtonYes = lv_btn_create(ui_DPanelReset);
    lv_obj_set_width(ui_DButtonYes, 100);
    lv_obj_set_height(ui_DButtonYes, 50);
    lv_obj_set_x(ui_DButtonYes, 60);
    lv_obj_set_y(ui_DButtonYes, 70);
    lv_obj_set_align(ui_DButtonYes, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_DButtonYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelYes = lv_label_create(ui_DButtonYes);
    lv_obj_set_width(ui_DLabelYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelYes, "Да");

    ui_DButtonNo = lv_btn_create(ui_DPanelReset);
    lv_obj_set_width(ui_DButtonNo, 100);
    lv_obj_set_height(ui_DButtonNo, 50);
    lv_obj_set_x(ui_DButtonNo, -60);
    lv_obj_set_y(ui_DButtonNo, 70);
    lv_obj_set_align(ui_DButtonNo, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_DButtonNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelNo = lv_label_create(ui_DButtonNo);
    lv_obj_set_width(ui_DLabelNo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelNo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelNo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelNo, "Нет");

    ui_DPanelRemove = lv_obj_create(ui_ScreenDarts);
    lv_obj_set_width(ui_DPanelRemove, lv_pct(100));
    lv_obj_set_height(ui_DPanelRemove, lv_pct(100));
    lv_obj_set_align(ui_DPanelRemove, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DPanelRemove, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_DPanelRemove, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_DPanelRemove, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelRemove, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DLabelRemove = lv_label_create(ui_DPanelRemove);
    lv_obj_set_width(ui_DLabelRemove, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelRemove, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DLabelRemove, -1);
    lv_obj_set_y(ui_DLabelRemove, 80);
    lv_obj_set_align(ui_DLabelRemove, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_DLabelRemove, "Отменить последний бросок?");
    lv_obj_set_style_text_color(ui_DLabelRemove, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DLabelRemove, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DButtonRemoveYes = lv_btn_create(ui_DPanelRemove);
    lv_obj_set_width(ui_DButtonRemoveYes, 100);
    lv_obj_set_height(ui_DButtonRemoveYes, 50);
    lv_obj_set_x(ui_DButtonRemoveYes, 60);
    lv_obj_set_y(ui_DButtonRemoveYes, 70);
    lv_obj_set_align(ui_DButtonRemoveYes, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_DButtonRemoveYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonRemoveYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelRemoveYes = lv_label_create(ui_DButtonRemoveYes);
    lv_obj_set_width(ui_DLabelRemoveYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelRemoveYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelRemoveYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelRemoveYes, "Да");

    ui_DButtonRemoveNo = lv_btn_create(ui_DPanelRemove);
    lv_obj_set_width(ui_DButtonRemoveNo, 100);
    lv_obj_set_height(ui_DButtonRemoveNo, 50);
    lv_obj_set_x(ui_DButtonRemoveNo, -60);
    lv_obj_set_y(ui_DButtonRemoveNo, 70);
    lv_obj_set_align(ui_DButtonRemoveNo, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_DButtonRemoveNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_DButtonRemoveNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DLabelRemoveNo = lv_label_create(ui_DButtonRemoveNo);
    lv_obj_set_width(ui_DLabelRemoveNo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DLabelRemoveNo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DLabelRemoveNo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DLabelRemoveNo, "Нет");

    ui_DPanelKB = lv_obj_create(ui_ScreenDarts);
    lv_obj_set_width(ui_DPanelKB, lv_pct(100));
    lv_obj_set_height(ui_DPanelKB, lv_pct(100));
    lv_obj_set_align(ui_DPanelKB, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DPanelKB, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_DPanelKB, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_DPanelKB, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DPanelKB, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DTextArea = lv_textarea_create(ui_DPanelKB);
    lv_obj_set_width(ui_DTextArea, lv_pct(100));
    lv_obj_set_height(ui_DTextArea, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_DTextArea, LV_ALIGN_TOP_MID);
    lv_textarea_set_max_length(ui_DTextArea, 4);
    lv_textarea_set_one_line(ui_DTextArea, true);
    lv_obj_set_style_text_align(ui_DTextArea, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DTextArea, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DKeyboard = lv_keyboard_create(ui_DPanelKB);
    lv_keyboard_set_map(ui_DKeyboard, LV_KEYBOARD_MODE_NUMBER, darts_kb_map_num, darts_kb_ctrl_num_map);
    lv_keyboard_set_mode(ui_DKeyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_width(ui_DKeyboard, lv_pct(100));
    lv_obj_set_height(ui_DKeyboard, lv_pct(66));
    lv_obj_set_align(ui_DKeyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_text_font(ui_DKeyboard, &ui_font_UbuntuCyrillic25, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_keyboard_set_textarea(ui_DKeyboard, ui_DTextArea);

}

///////////////////// EXPORT ////////////////////

void gui_darts_create()
{
    ui_ScreenDarts_screen_init();

    lv_obj_add_event_cb(ui_ScreenDarts, ui_event_ScreenDarts, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_DLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DLabelReset, ui_event_onLabelReset, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonYes, ui_event_DButtonYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonNo, ui_event_DButtonNo, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_DPanelPly1, ui_event_DPanelPly1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DPanelPly2, ui_event_DPanelPly2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DPanelPly3, ui_event_DPanelPly3, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_DLabelScore, ui_event_DLabelScore, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonSector, ui_event_DButtonSector, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonDouble, ui_event_DButtonDouble, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonTriple, ui_event_DButtonTriple, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_DTextArea, ui_event_DTextArea, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_DLabelTrash, ui_event_DLabelTrash, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonRemoveYes, ui_event_DButtonRemoveYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DButtonRemoveNo, ui_event_DButtonRemoveNo, LV_EVENT_ALL, NULL);

}

void gui_darts_delete()
{
    if (ui_ScreenDarts != NULL)
    {
        lv_obj_del(ui_ScreenDarts);
        ui_ScreenDarts = NULL;
    }
}