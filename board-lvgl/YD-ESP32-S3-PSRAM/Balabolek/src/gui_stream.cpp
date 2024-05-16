#include "gui_stream.h"
#include "gui_main.h"
#include "gui.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenStream;

static lv_obj_t* ui_TVLabelHome;
static lv_obj_t* ui_TVLabelReset;
static lv_obj_t* ui_TVPanelPlayers;
static lv_obj_t* ui_TVLabelPly1;
static lv_obj_t* ui_TVLabelPly2;
static lv_obj_t* ui_TVPanelGame;
static lv_obj_t* ui_TVLabelGameScore1;
static lv_obj_t* ui_TVLabelGameScore2;
static lv_obj_t* ui_TVLabelGameScoreMax;
static lv_obj_t* ui_TVPanelFrame;
static lv_obj_t* ui_TVLabelFrameScore1;
static lv_obj_t* ui_TVLabelFrameScoreReset;
static lv_obj_t* ui_TVLabelFrameScore2;
static lv_obj_t* ui_TVPanelGameReset;
static lv_obj_t* ui_TVLabelGameResetQ;
static lv_obj_t* ui_TVBtnGameResetYes;
static lv_obj_t* ui_TVLabelGameResetYes;
static lv_obj_t* ui_TVBtnGameResetNo;
static lv_obj_t* ui_TVLabelGameResetNo;
static lv_obj_t* ui_TVPanelFrameReset;
static lv_obj_t* ui_TVLabelFrameResetQ;
static lv_obj_t* ui_TVBtnFrameResetYes;
static lv_obj_t* ui_TVLabelFrameResetYes;
static lv_obj_t* ui_TVBtnFrameResetNo;
static lv_obj_t* ui_TVLabelFrameResetNo;
static lv_obj_t* ui_TVKeyboardScore;
static lv_obj_t* ui_TVNameKeyboard;

static lv_obj_t* labelToUpdate = NULL;

///////////////////// CALLBACKS ////////////////////

static void ui_event_updatePly1Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER1, newName);
	lv_label_set_text(ui_TVLabelPly1, newName);
	
	gui_publishCurrentState();
}
static void ui_event_updatePly2Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER2, newName);
	lv_label_set_text(ui_TVLabelPly2, newName);

	gui_publishCurrentState();
}

static void ui_event_updateGameScore1(lv_obj_t* obj)
{
	int16_t score;

    if (ui_normalize_score(lv_textarea_get_text(obj), &score) == true)
    {
        boardPublishing.tvGameScorePly1 = score;
    }
    else
    {
        boardPublishing.tvGameScorePly1 += score;
    }

    lv_label_set_text_fmt(ui_TVLabelGameScore1, "%d", boardPublishing.tvGameScorePly1);

	gui_publishCurrentState();
	gui_sendTelegaTVGameScoreMessage();
	gui_sayTVGameResult();
}
static void ui_event_updateGameScore2(lv_obj_t* obj)
{
	int16_t score;

    if (ui_normalize_score(lv_textarea_get_text(obj), &score) == true)
    {
        boardPublishing.tvGameScorePly2 = score;
    }
    else
    {
        boardPublishing.tvGameScorePly2 += score;
    }

    lv_label_set_text_fmt(ui_TVLabelGameScore2, "%d", boardPublishing.tvGameScorePly2);

	gui_publishCurrentState();
	gui_sendTelegaTVGameScoreMessage();
	gui_sayTVGameResult();
}
static void ui_event_updateGameScoreMax(lv_obj_t* obj)
{
	int16_t score;

    if (ui_normalize_score(lv_textarea_get_text(obj), &score) == true)
    {
        boardPublishing.tvGameScoreMax = score;
    }
    else
    {
        boardPublishing.tvGameScoreMax += score;
    }

	lv_label_set_text_fmt(ui_TVLabelGameScoreMax, "(%d)", boardPublishing.tvGameScoreMax);

	gui_publishCurrentState();
}
static void ui_event_updateFrameScore1(lv_obj_t* obj)
{
	int16_t score;

    if (ui_normalize_score(lv_textarea_get_text(obj), &score) == true)
    {
        boardPublishing.tvFrameScorePly1 = score;
    }
    else
    {
        boardPublishing.tvFrameScorePly1 += score;
    }

    lv_label_set_text_fmt(ui_TVLabelFrameScore1, "%d", boardPublishing.tvFrameScorePly1);

	gui_publishCurrentState();
	gui_sendTelegaTVFrameScoreMessage();
	gui_sayTVFrameResult();
}
static void ui_event_updateFrameScore2(lv_obj_t* obj)
{
	int16_t score;

    if (ui_normalize_score(lv_textarea_get_text(obj), &score) == true)
    {
        boardPublishing.tvFrameScorePly2 = score;
    }
    else
    {
        boardPublishing.tvFrameScorePly2 += score;
    }

    lv_label_set_text_fmt(ui_TVLabelFrameScore2, "%d", boardPublishing.tvFrameScorePly2);

	gui_publishCurrentState();
	gui_sendTelegaTVFrameScoreMessage();
	gui_sayTVFrameResult();
}

///////////////////// FUNCTIONS ////////////////////

static void ui_event_onLabelHome(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_main_create);
	}
}

static void ui_event_onTVLabelPlyUpdate(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if(event_code == LV_EVENT_LONG_PRESSED)
	{
		if(target == ui_TVLabelPly1)
		{
			ui_comp_set_callback(ui_TVNameKeyboard, ui_event_updatePly1Name);
		}
		else if(target == ui_TVLabelPly2)
		{
			ui_comp_set_callback(ui_TVNameKeyboard, ui_event_updatePly2Name);
		}
		else
		{
			ui_comp_set_callback(ui_TVNameKeyboard, NULL);
		}

		lv_textarea_set_text(ui_comp_get_child(ui_TVNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), lv_label_get_text(target));

        _ui_flag_modify(ui_TVNameKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_onTVLabelScoreUpdate(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t* labelToUpdate = static_cast<lv_obj_t*>(lv_event_get_target(e));

	if (event_code == LV_EVENT_CLICKED)
	{
		ui_comp_set_callback(ui_TVKeyboardScore, NULL);

		if (labelToUpdate == ui_TVLabelGameScoreMax)
		{
            lv_textarea_set_text(ui_comp_get_child(ui_TVKeyboardScore, UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE), "=");
    	    lv_label_set_text(ui_comp_get_child(ui_TVKeyboardScore, UI_COMP_SCOREKEYBOARD_LABELUPDATEDSCORE), lv_label_get_text(labelToUpdate));
			
			ui_comp_set_callback(ui_TVKeyboardScore, ui_event_updateGameScoreMax);
		}
		else
		{
			if(gameHasSatrted == false)
			{
				_ui_flag_modify(ui_TVPanelGameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
				return;
			}

            lv_textarea_set_text(ui_comp_get_child(ui_TVKeyboardScore, UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE), "+");
    		lv_label_set_text(ui_comp_get_child(ui_TVKeyboardScore, UI_COMP_SCOREKEYBOARD_LABELUPDATEDSCORE), lv_label_get_text(labelToUpdate));

			if (labelToUpdate == ui_TVLabelGameScore1)
			{
				ui_comp_set_callback(ui_TVKeyboardScore, ui_event_updateGameScore1);
			}
			else if (labelToUpdate == ui_TVLabelGameScore2)
			{
				ui_comp_set_callback(ui_TVKeyboardScore, ui_event_updateGameScore2);
			}
			else if (labelToUpdate == ui_TVLabelFrameScore1)
			{
				ui_comp_set_callback(ui_TVKeyboardScore, ui_event_updateFrameScore1);
			}
			else if (labelToUpdate == ui_TVLabelFrameScore2)
			{
				ui_comp_set_callback(ui_TVKeyboardScore, ui_event_updateFrameScore2);
			}
		}
        
        _ui_flag_modify(ui_TVKeyboardScore, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	}
}

static void ui_event_onLabelGameReset(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_TVPanelGameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	}
}
static void ui_event_Game_ResetNo(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_TVPanelGameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}
static void ui_event_Game_ResetYes(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		boardPublishing.tvGameScorePly1 = 0;
		boardPublishing.tvGameScorePly2 = 0;

		boardPublishing.tvFrameScorePly1 = 0;
		boardPublishing.tvFrameScorePly2 = 0;

		lv_label_set_text_fmt(ui_TVLabelGameScore1, "%d", boardPublishing.tvGameScorePly1);
		lv_label_set_text_fmt(ui_TVLabelGameScore2, "%d", boardPublishing.tvGameScorePly2);

		lv_label_set_text_fmt(ui_TVLabelFrameScore1, "%d", boardPublishing.tvFrameScorePly1);
		lv_label_set_text_fmt(ui_TVLabelFrameScore2, "%d", boardPublishing.tvFrameScorePly2);

		gameHasSatrted = true;

		gui_publishCurrentState();

		gui_sendTelegaTVGameScoreMessage();

		gui_sendTelegaPollMessage(TWO);

		gui_sayTVGameResult();

		_ui_flag_modify(ui_TVPanelGameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}

static void ui_event_onLabelFrameReset(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_TVPanelFrameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	}
}
static void ui_event_Frame_ResetNo(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_TVPanelFrameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}
static void ui_event_Frame_ResetYes(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		boardPublishing.tvFrameScorePly1 = 0;
		boardPublishing.tvFrameScorePly2 = 0;

		lv_label_set_text_fmt(ui_TVLabelFrameScore1, "%d", boardPublishing.tvFrameScorePly1);
		lv_label_set_text_fmt(ui_TVLabelFrameScore2, "%d", boardPublishing.tvFrameScorePly2);

		gui_publishCurrentState();

		gui_sendTelegaTVFrameScoreMessage(false);

		gui_sayTVFrameResult();

		_ui_flag_modify(ui_TVPanelFrameReset, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}

static void ui_event_ScreenStream(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_SCREEN_LOAD_START)
	{
		lv_label_set_text(ui_TVLabelPly1, gui_getPlayerName(PLAYER1));
		lv_label_set_text(ui_TVLabelPly2, gui_getPlayerName(PLAYER2));

		lv_label_set_text_fmt(ui_TVLabelGameScore1, "%d", boardPublishing.tvGameScorePly1);
		lv_label_set_text_fmt(ui_TVLabelGameScore2, "%d", boardPublishing.tvGameScorePly2);
		lv_label_set_text_fmt(ui_TVLabelGameScoreMax, "(%d)", boardPublishing.tvGameScoreMax);

		lv_label_set_text_fmt(ui_TVLabelFrameScore1, "%d", boardPublishing.tvFrameScorePly1);
		lv_label_set_text_fmt(ui_TVLabelFrameScore2, "%d", boardPublishing.tvFrameScorePly2);
	}
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenStream_screen_init(void)
{
	ui_ScreenStream = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_ScreenStream, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_image_src(ui_ScreenStream, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_ScreenStream, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_ScreenStream, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_ScreenStream, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_ScreenStream, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelHome = lv_label_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVLabelHome, 110);
	lv_obj_set_height(ui_TVLabelHome, 50);
	lv_obj_set_x(ui_TVLabelHome, -160);
	lv_obj_set_y(ui_TVLabelHome, 125);
	lv_obj_set_align(ui_TVLabelHome, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelHome, LV_SYMBOL_HOME " Назад");
	lv_obj_add_flag(ui_TVLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_TVLabelHome, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelReset = lv_label_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVLabelReset, 180);
	lv_obj_set_height(ui_TVLabelReset, 50);
	lv_obj_set_x(ui_TVLabelReset, 120);
	lv_obj_set_y(ui_TVLabelReset, 125);
	lv_obj_set_align(ui_TVLabelReset, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelReset, "Новый матч " LV_SYMBOL_REFRESH);
	lv_obj_add_flag(ui_TVLabelReset, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_TVLabelReset, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVPanelPlayers = lv_obj_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVPanelPlayers, 420);
	lv_obj_set_height(ui_TVPanelPlayers, 50);
	lv_obj_set_x(ui_TVPanelPlayers, 0);
	lv_obj_set_y(ui_TVPanelPlayers, 35);
	lv_obj_set_align(ui_TVPanelPlayers, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(ui_TVPanelPlayers, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVPanelPlayers, lv_color_hex(0x1E5016), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVPanelPlayers, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_TVPanelPlayers, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_TVPanelPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_TVPanelPlayers, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVPanelPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVPanelPlayers, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelPly1 = lv_label_create(ui_TVPanelPlayers);
	lv_obj_set_width(ui_TVLabelPly1, lv_pct(45));
	lv_obj_set_height(ui_TVLabelPly1, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelPly1, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_TVLabelPly1, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_add_flag(ui_TVLabelPly1, LV_OBJ_FLAG_CLICKABLE);     /// Flags

	ui_TVLabelPly2 = lv_label_create(ui_TVPanelPlayers);
	lv_obj_set_width(ui_TVLabelPly2, lv_pct(45));
	lv_obj_set_height(ui_TVLabelPly2, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelPly2, LV_ALIGN_RIGHT_MID);
	lv_label_set_long_mode(ui_TVLabelPly2, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_add_flag(ui_TVLabelPly2, LV_OBJ_FLAG_CLICKABLE);     /// Flags

	ui_TVPanelGame = lv_obj_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVPanelGame, 420);
	lv_obj_set_height(ui_TVPanelGame, 60);
	lv_obj_set_x(ui_TVPanelGame, 0);
	lv_obj_set_y(ui_TVPanelGame, -65);
	lv_obj_set_align(ui_TVPanelGame, LV_ALIGN_BOTTOM_MID);
	lv_obj_clear_flag(ui_TVPanelGame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVPanelGame, lv_color_hex(0x1E5016), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVPanelGame, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_TVPanelGame, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_TVPanelGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_TVPanelGame, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVPanelGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVPanelGame, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_TVPanelGame, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelGameScore1 = lv_label_create(ui_TVPanelGame);
	lv_obj_set_width(ui_TVLabelGameScore1, lv_pct(40));
	lv_obj_set_height(ui_TVLabelGameScore1, LV_SIZE_CONTENT);    /// 90
	lv_obj_set_x(ui_TVLabelGameScore1, -10);
	lv_obj_set_y(ui_TVLabelGameScore1, 0);
	lv_obj_set_align(ui_TVLabelGameScore1, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_TVLabelGameScore1, LV_LABEL_LONG_SCROLL);
	lv_obj_add_flag(ui_TVLabelGameScore1, LV_OBJ_FLAG_CLICKABLE);     /// Flags

	ui_TVLabelGameScore2 = lv_label_create(ui_TVPanelGame);
	lv_obj_set_width(ui_TVLabelGameScore2, lv_pct(40));
	lv_obj_set_height(ui_TVLabelGameScore2, LV_SIZE_CONTENT);    /// 90
	lv_obj_set_x(ui_TVLabelGameScore2, 10);
	lv_obj_set_y(ui_TVLabelGameScore2, 0);
	lv_obj_set_align(ui_TVLabelGameScore2, LV_ALIGN_RIGHT_MID);
	lv_label_set_long_mode(ui_TVLabelGameScore2, LV_LABEL_LONG_SCROLL);
	lv_obj_add_flag(ui_TVLabelGameScore2, LV_OBJ_FLAG_CLICKABLE);     /// Flags

	ui_TVLabelGameScoreMax = lv_label_create(ui_TVPanelGame);
	lv_obj_set_width(ui_TVLabelGameScoreMax, lv_pct(20));
	lv_obj_set_height(ui_TVLabelGameScoreMax, LV_SIZE_CONTENT);    /// 100
	lv_obj_set_align(ui_TVLabelGameScoreMax, LV_ALIGN_CENTER);
	lv_label_set_long_mode(ui_TVLabelGameScoreMax, LV_LABEL_LONG_SCROLL);
	lv_obj_add_flag(ui_TVLabelGameScoreMax, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_color(ui_TVLabelGameScoreMax, lv_color_hex(0xBDBABA), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVLabelGameScoreMax, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_TVLabelGameScoreMax, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVPanelFrame = lv_obj_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVPanelFrame, 420);
	lv_obj_set_height(ui_TVPanelFrame, LV_SIZE_CONTENT);    /// 60
	lv_obj_set_x(ui_TVPanelFrame, 0);
	lv_obj_set_y(ui_TVPanelFrame, -20);
	lv_obj_set_align(ui_TVPanelFrame, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_TVPanelFrame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVPanelFrame, lv_color_hex(0x1E5016), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVPanelFrame, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_TVPanelFrame, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_TVPanelFrame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_TVPanelFrame, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVPanelFrame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVPanelFrame, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_TVPanelFrame, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameScore1 = lv_label_create(ui_TVPanelFrame);
	lv_obj_set_width(ui_TVLabelFrameScore1, lv_pct(45));
	lv_obj_set_height(ui_TVLabelFrameScore1, LV_SIZE_CONTENT);    /// 90
	lv_obj_set_align(ui_TVLabelFrameScore1, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_TVLabelFrameScore1, LV_LABEL_LONG_SCROLL);
	lv_obj_add_flag(ui_TVLabelFrameScore1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_TVLabelFrameScore1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameScoreReset = lv_label_create(ui_TVPanelFrame);
	lv_obj_set_width(ui_TVLabelFrameScoreReset, 40);
	lv_obj_set_height(ui_TVLabelFrameScoreReset, LV_SIZE_CONTENT);    /// 40
	lv_obj_set_align(ui_TVLabelFrameScoreReset, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelFrameScoreReset, LV_SYMBOL_REFRESH);
	lv_obj_add_flag(ui_TVLabelFrameScoreReset, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_font(ui_TVLabelFrameScoreReset, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameScore2 = lv_label_create(ui_TVPanelFrame);
	lv_obj_set_width(ui_TVLabelFrameScore2, lv_pct(45));
	lv_obj_set_height(ui_TVLabelFrameScore2, LV_SIZE_CONTENT);    /// 90
	lv_obj_set_align(ui_TVLabelFrameScore2, LV_ALIGN_RIGHT_MID);
	lv_label_set_long_mode(ui_TVLabelFrameScore2, LV_LABEL_LONG_SCROLL);
	lv_obj_add_flag(ui_TVLabelFrameScore2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_TVLabelFrameScore2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVPanelGameReset = lv_obj_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVPanelGameReset, 430);
	lv_obj_set_height(ui_TVPanelGameReset, 225);
	lv_obj_set_x(ui_TVPanelGameReset, 0);
	lv_obj_set_y(ui_TVPanelGameReset, 30);
	lv_obj_set_align(ui_TVPanelGameReset, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(ui_TVPanelGameReset, LV_OBJ_FLAG_HIDDEN);     /// Flags
	lv_obj_clear_flag(ui_TVPanelGameReset, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVPanelGameReset, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVPanelGameReset, 235, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_TVPanelGameReset, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_TVPanelGameReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelGameResetQ = lv_label_create(ui_TVPanelGameReset);
	lv_obj_set_width(ui_TVLabelGameResetQ, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelGameResetQ, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_TVLabelGameResetQ, 0);
	lv_obj_set_y(ui_TVLabelGameResetQ, 35);
	lv_obj_set_align(ui_TVLabelGameResetQ, LV_ALIGN_TOP_MID);
	lv_label_set_text(ui_TVLabelGameResetQ, "Начать новый матч?");
	lv_obj_set_style_text_color(ui_TVLabelGameResetQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVLabelGameResetQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVBtnGameResetYes = lv_btn_create(ui_TVPanelGameReset);
	lv_obj_set_width(ui_TVBtnGameResetYes, 165);
	lv_obj_set_height(ui_TVBtnGameResetYes, 65);
	lv_obj_set_x(ui_TVBtnGameResetYes, -110);
	lv_obj_set_y(ui_TVBtnGameResetYes, 60);
	lv_obj_set_align(ui_TVBtnGameResetYes, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_TVBtnGameResetYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_TVBtnGameResetYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVBtnGameResetYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVBtnGameResetYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVBtnGameResetYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelGameResetYes = lv_label_create(ui_TVBtnGameResetYes);
	lv_obj_set_width(ui_TVLabelGameResetYes, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelGameResetYes, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelGameResetYes, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelGameResetYes, "ДА");

	ui_TVBtnGameResetNo = lv_btn_create(ui_TVPanelGameReset);
	lv_obj_set_width(ui_TVBtnGameResetNo, 165);
	lv_obj_set_height(ui_TVBtnGameResetNo, 65);
	lv_obj_set_x(ui_TVBtnGameResetNo, 110);
	lv_obj_set_y(ui_TVBtnGameResetNo, 60);
	lv_obj_set_align(ui_TVBtnGameResetNo, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_TVBtnGameResetNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_TVBtnGameResetNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVBtnGameResetNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVBtnGameResetNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVBtnGameResetNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelGameResetNo = lv_label_create(ui_TVBtnGameResetNo);
	lv_obj_set_width(ui_TVLabelGameResetNo, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelGameResetNo, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelGameResetNo, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelGameResetNo, "НЕТ");

	ui_TVPanelFrameReset = lv_obj_create(ui_ScreenStream);
	lv_obj_set_width(ui_TVPanelFrameReset, 430);
	lv_obj_set_height(ui_TVPanelFrameReset, 225);
	lv_obj_set_x(ui_TVPanelFrameReset, 0);
	lv_obj_set_y(ui_TVPanelFrameReset, 30);
	lv_obj_set_align(ui_TVPanelFrameReset, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(ui_TVPanelFrameReset, LV_OBJ_FLAG_HIDDEN);     /// Flags
	lv_obj_clear_flag(ui_TVPanelFrameReset, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVPanelFrameReset, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVPanelFrameReset, 235, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_TVPanelFrameReset, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_TVPanelFrameReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameResetQ = lv_label_create(ui_TVPanelFrameReset);
	lv_obj_set_width(ui_TVLabelFrameResetQ, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelFrameResetQ, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_TVLabelFrameResetQ, 0);
	lv_obj_set_y(ui_TVLabelFrameResetQ, 35);
	lv_obj_set_align(ui_TVLabelFrameResetQ, LV_ALIGN_TOP_MID);
	lv_label_set_text(ui_TVLabelFrameResetQ, "Сбросить счёт в партии?");
	lv_obj_set_style_text_color(ui_TVLabelFrameResetQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_TVLabelFrameResetQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVBtnFrameResetYes = lv_btn_create(ui_TVPanelFrameReset);
	lv_obj_set_width(ui_TVBtnFrameResetYes, 165);
	lv_obj_set_height(ui_TVBtnFrameResetYes, 65);
	lv_obj_set_x(ui_TVBtnFrameResetYes, -110);
	lv_obj_set_y(ui_TVBtnFrameResetYes, 60);
	lv_obj_set_align(ui_TVBtnFrameResetYes, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_TVBtnFrameResetYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_TVBtnFrameResetYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVBtnFrameResetYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVBtnFrameResetYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVBtnFrameResetYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameResetYes = lv_label_create(ui_TVBtnFrameResetYes);
	lv_obj_set_width(ui_TVLabelFrameResetYes, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelFrameResetYes, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelFrameResetYes, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelFrameResetYes, "ДА");

	ui_TVBtnFrameResetNo = lv_btn_create(ui_TVPanelFrameReset);
	lv_obj_set_width(ui_TVBtnFrameResetNo, 165);
	lv_obj_set_height(ui_TVBtnFrameResetNo, 65);
	lv_obj_set_x(ui_TVBtnFrameResetNo, 110);
	lv_obj_set_y(ui_TVBtnFrameResetNo, 60);
	lv_obj_set_align(ui_TVBtnFrameResetNo, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_TVBtnFrameResetNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_TVBtnFrameResetNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_TVBtnFrameResetNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TVBtnFrameResetNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_TVBtnFrameResetNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_TVLabelFrameResetNo = lv_label_create(ui_TVBtnFrameResetNo);
	lv_obj_set_width(ui_TVLabelFrameResetNo, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_TVLabelFrameResetNo, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_TVLabelFrameResetNo, LV_ALIGN_CENTER);
	lv_label_set_text(ui_TVLabelFrameResetNo, "НЕТ");

	ui_TVKeyboardScore = ui_ScoreKeyboard_create(ui_ScreenStream);
    lv_obj_set_x(ui_TVKeyboardScore, 0);
    lv_obj_set_y(ui_TVKeyboardScore, 0);

	ui_TVNameKeyboard = ui_NameKeyboard_create(ui_ScreenStream);
    lv_obj_set_x(ui_TVNameKeyboard, 0);
    lv_obj_set_y(ui_TVNameKeyboard, 0);
}

///////////////////// EXPORT ////////////////////

void gui_stream_create()
{
	ui_ScreenStream_screen_init();

	lv_obj_add_event_cb(ui_ScreenStream, ui_event_ScreenStream, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelPly1, ui_event_onTVLabelPlyUpdate, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVLabelPly2, ui_event_onTVLabelPlyUpdate, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelGameScore1, ui_event_onTVLabelScoreUpdate, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVLabelGameScore2, ui_event_onTVLabelScoreUpdate, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVLabelGameScoreMax, ui_event_onTVLabelScoreUpdate, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelFrameScore1, ui_event_onTVLabelScoreUpdate, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVLabelFrameScore2, ui_event_onTVLabelScoreUpdate, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelReset, ui_event_onLabelGameReset, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVBtnGameResetYes, ui_event_Game_ResetYes, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVBtnGameResetNo, ui_event_Game_ResetNo, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_TVLabelFrameScoreReset, ui_event_onLabelFrameReset, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVBtnFrameResetYes, ui_event_Frame_ResetYes, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_TVBtnFrameResetNo, ui_event_Frame_ResetNo, LV_EVENT_ALL, NULL);
}

