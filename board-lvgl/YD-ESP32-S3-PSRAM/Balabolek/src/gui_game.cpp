#include "gui_game.h"
#include "gui_main.h"
#include "gui.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenGame;

static lv_obj_t* ui_GLabelHome;
static lv_obj_t* ui_GLabelRefresh;
static lv_obj_t* ui_GSwitchPlyCount;
static lv_obj_t* ui_GLabel2;
static lv_obj_t* ui_GLabel3;
static lv_obj_t* ui_GPanelPool2;
static lv_obj_t* ui_PanelPool2Ply1;
static lv_obj_t* ui_GImageBreak0;
static lv_obj_t* ui_GImageBreak180;
static lv_obj_t* ui_PanelPool2Ply2;
static lv_obj_t* ui_GPanelPool3;
static lv_obj_t* ui_PanelPool3Ply1;
static lv_obj_t* ui_PanelPool3Ply2;
static lv_obj_t* ui_PanelPool3Ply3;

static lv_obj_t* ui_MBPanelPool;
static lv_obj_t* ui_MBLabelPoolResetQ;
static lv_obj_t* ui_MBBtnPoolResetYes;
static lv_obj_t* ui_MBLabelPoolResetYes;
static lv_obj_t* ui_MBBtnPoolResetNo;
static lv_obj_t* ui_MBLabelPoolResetNo;

static lv_obj_t* ui_NameKeyboard;

static lv_timer_t* scoreTimer = NULL;

///////////////////// FUNCTIONS ////////////////////

typedef enum
{
	DECREASE = -1,
	INCREASE = 1
} ScoreAction;

static void ui_event_update2Ply1Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER1, newName);
	lv_label_set_text(ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), newName);
}
static void ui_event_update2Ply2Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER2, newName);
	lv_label_set_text(ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), newName);
}
static void ui_event_update3Ply1Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER_EX1, newName);
	lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), newName);
}
static void ui_event_update3Ply2Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER_EX2, newName);
	lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), newName);
}
static void ui_event_update3Ply3Name(lv_obj_t* obj)
{
	const char* newName = lv_textarea_get_text(obj);
	gui_setPlayerName(PLAYER_EX3, newName);
	lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), newName);
}

static void ui_switchBreak()
{
	if(boardPublishing.gamePlyBreak == LEFT)
	{
		boardPublishing.gamePlyBreak = RIGHT;
		lv_obj_remove_flag(ui_GImageBreak180, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_GImageBreak0, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		boardPublishing.gamePlyBreak = LEFT;
		lv_obj_remove_flag(ui_GImageBreak0, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui_GImageBreak180, LV_OBJ_FLAG_HIDDEN);
	}
}

static void ui_hideScorePlusMinus(lv_timer_t* timer)
{
	_ui_flag_modify((lv_obj_t*)timer->user_data, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

	lv_timer_del(scoreTimer);
	scoreTimer = NULL;
}

static void updateScoreInComponent(lv_obj_t** comp_PanelPoolPlayer, ScoreAction action)
{
	lv_obj_t* parent = comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER];

	if (parent == ui_PanelPool2Ply1)
	{
		boardPublishing.gamePly1Score += action;
		lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", boardPublishing.gamePly1Score);
	}
	else if (parent == ui_PanelPool2Ply2)
	{
		boardPublishing.gamePly2Score += action;
		lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", boardPublishing.gamePly2Score);
	}
	else if (parent == ui_PanelPool3Ply1)
	{
		boardPublishing.gameExPly1Score += action;
		lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", boardPublishing.gameExPly1Score);
	}
	else if (parent == ui_PanelPool3Ply2)
	{
		boardPublishing.gameExPly2Score += action;
		lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", boardPublishing.gameExPly2Score);
	}
	else if (parent == ui_PanelPool3Ply3)
	{
		boardPublishing.gameExPly3Score += action;
		lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", boardPublishing.gameExPly3Score);
	}

	if (boardPublishing.gamePlyCount == TWO)
	{
		boardPublishing.tvGameScorePly1 = boardPublishing.gamePly1Score;
		boardPublishing.tvGameScorePly2 = boardPublishing.gamePly2Score;

		ui_switchBreak();
	}

	gui_publishCurrentState();

	gui_sendTelegaGameScoreMessage(boardPublishing.gamePlyCount);

	gui_sayGameResult(boardPublishing.gamePlyCount);
}

static void ui_event_onLabelHome(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_main_create);
	}
}

static void ui_event_onLabelReset(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	}
}

static void ui_event_PSwitchPlyCount(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

	if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
	{
		boardPublishing.gamePlyCount = TWO;

		_ui_flag_modify(ui_GPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
		_ui_flag_modify(ui_GPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
	if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
	{
		boardPublishing.gamePlyCount = THREE;

		_ui_flag_modify(ui_GPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
		_ui_flag_modify(ui_GPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	}
}

static void ui_event_PImageBreak(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		ui_switchBreak();
	}
}

static void ui_event_MB_ResetNo(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_flag_modify(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}

static void ui_event_MB_ResetYes(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		lv_obj_t* scoreLabel;

		if (boardPublishing.gamePlyCount == THREE)
		{
			boardPublishing.gameExPly1Score = 0;
			boardPublishing.gameExPly2Score = 0;
			boardPublishing.gameExPly3Score = 0;

			scoreLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
			lv_label_set_text(scoreLabel, "0");

			scoreLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
			lv_label_set_text(scoreLabel, "0");

			scoreLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
			lv_label_set_text(scoreLabel, "0");
		}
		else
		{
			boardPublishing.gamePly1Score = 0;
			boardPublishing.gamePly2Score = 0;

			boardPublishing.tvGameScorePly1 = 0;
			boardPublishing.tvGameScorePly2 = 0;

			scoreLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
			lv_label_set_text(scoreLabel, "0");

			scoreLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
			lv_label_set_text(scoreLabel, "0");
		}

		gameHasSatrted = true;

		gui_publishCurrentState();

		gui_sendTelegaGameScoreMessage(boardPublishing.gamePlyCount);
		gui_sendTelegaPollMessage(boardPublishing.gamePlyCount);
		gui_sayGameResult(boardPublishing.gamePlyCount);

		_ui_flag_modify(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	}
}

static void ui_event_ScreenGame(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_SCREEN_LOAD_START)
	{
		lv_obj_t* plyLabel;

		plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
		lv_label_set_text(plyLabel, gui_getPlayerName(PLAYER1));

		plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
		lv_label_set_text(plyLabel, gui_getPlayerName(PLAYER2));

		plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
		lv_label_set_text(plyLabel, gui_getPlayerName(PLAYER_EX1));

		plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
		lv_label_set_text(plyLabel, gui_getPlayerName(PLAYER_EX2));

		plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
		lv_label_set_text(plyLabel, gui_getPlayerName(PLAYER_EX3));

		lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", boardPublishing.gamePly1Score);
		lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", boardPublishing.gamePly2Score);
		lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", boardPublishing.gameExPly1Score);
		lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", boardPublishing.gameExPly2Score);
		lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", boardPublishing.gameExPly3Score);

		if(boardPublishing.gamePlyBreak == LEFT)
		{
			lv_obj_remove_flag(ui_GImageBreak0, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui_GImageBreak180, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_obj_remove_flag(ui_GImageBreak180, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui_GImageBreak0, LV_OBJ_FLAG_HIDDEN);
		}

		if (boardPublishing.gamePlyCount == TWO)
		{
			_ui_flag_modify(ui_GPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
			_ui_flag_modify(ui_GPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

			_ui_state_modify(ui_GSwitchPlyCount, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
		}
		else
		{
			_ui_flag_modify(ui_GPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
			_ui_flag_modify(ui_GPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
 
			_ui_state_modify(ui_GSwitchPlyCount, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
		}
	}
	else if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
	{
		if (scoreTimer != NULL)
		{
			lv_timer_del(scoreTimer);
			scoreTimer = NULL;
		}
	}
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenGame_screen_init(void)
{
	ui_ScreenGame = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_ScreenGame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_image_src(ui_ScreenGame, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_ScreenGame, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_ScreenGame, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_ScreenGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_ScreenGame, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_GLabelHome = lv_label_create(ui_ScreenGame);
	lv_obj_set_width(ui_GLabelHome, 110);
	lv_obj_set_height(ui_GLabelHome, 50);
	lv_obj_set_x(ui_GLabelHome, -160);
	lv_obj_set_y(ui_GLabelHome, 125);
	lv_obj_set_align(ui_GLabelHome, LV_ALIGN_CENTER);
	lv_label_set_text(ui_GLabelHome, LV_SYMBOL_HOME " Назад");
	lv_obj_add_flag(ui_GLabelHome, LV_OBJ_FLAG_CLICKABLE);   /// Flags
	lv_obj_set_style_text_align(ui_GLabelHome, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_GLabelRefresh = lv_label_create(ui_ScreenGame);
	lv_obj_set_width(ui_GLabelRefresh, 145);
	lv_obj_set_height(ui_GLabelRefresh, 50);
	lv_obj_set_x(ui_GLabelRefresh, 140);
	lv_obj_set_y(ui_GLabelRefresh, 125);
	lv_obj_set_align(ui_GLabelRefresh, LV_ALIGN_CENTER);
	lv_label_set_text(ui_GLabelRefresh, "Новый " LV_SYMBOL_REFRESH);
	lv_obj_add_flag(ui_GLabelRefresh, LV_OBJ_FLAG_CLICKABLE);   /// Flags
	lv_obj_set_style_text_align(ui_GLabelRefresh, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_GSwitchPlyCount = lv_switch_create(ui_ScreenGame);
	lv_obj_set_width(ui_GSwitchPlyCount, 64);
	lv_obj_set_height(ui_GSwitchPlyCount, 32);
	lv_obj_set_x(ui_GSwitchPlyCount, 0);
	lv_obj_set_y(ui_GSwitchPlyCount, 115);
	lv_obj_set_align(ui_GSwitchPlyCount, LV_ALIGN_CENTER);

	lv_obj_set_style_bg_color(ui_GSwitchPlyCount, lv_color_hex(0x836529), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_GSwitchPlyCount, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_GSwitchPlyCount, lv_color_hex(0x004C00), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_GSwitchPlyCount, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_bg_color(ui_GSwitchPlyCount, lv_color_hex(0x004C00), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_GSwitchPlyCount, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_GSwitchPlyCount, lv_color_hex(0x836529), LV_PART_KNOB | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_GSwitchPlyCount, 255, LV_PART_KNOB | LV_STATE_CHECKED);

	ui_GLabel2 = lv_label_create(ui_ScreenGame);
	lv_obj_set_width(ui_GLabel2, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_GLabel2, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(ui_GLabel2, -45);
	lv_obj_set_y(ui_GLabel2, 115);
	lv_obj_set_align(ui_GLabel2, LV_ALIGN_CENTER);
	lv_label_set_text(ui_GLabel2, "2");

	ui_GLabel3 = lv_label_create(ui_ScreenGame);
	lv_obj_set_width(ui_GLabel3, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_GLabel3, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(ui_GLabel3, 45);
	lv_obj_set_y(ui_GLabel3, 115);
	lv_obj_set_align(ui_GLabel3, LV_ALIGN_CENTER);
	lv_label_set_text(ui_GLabel3, "3");

	ui_GPanelPool2 = lv_obj_create(ui_ScreenGame);
	lv_obj_set_width(ui_GPanelPool2, 430);
	lv_obj_set_height(ui_GPanelPool2, 225);
	lv_obj_set_x(ui_GPanelPool2, 0);
	lv_obj_set_y(ui_GPanelPool2, 30);
	lv_obj_set_align(ui_GPanelPool2, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(ui_GPanelPool2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_GPanelPool2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_GPanelPool2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_GPanelPool2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_PanelPool2Ply1 = ui_PanelPoolPlayer_create(ui_GPanelPool2);
	lv_obj_set_x(ui_PanelPool2Ply1, -125);
	lv_obj_set_y(ui_PanelPool2Ply1, 0);

    ui_GImageBreak0 = lv_img_create(ui_GPanelPool2);
    lv_img_set_src(ui_GImageBreak0, &ui_img_break0_png);
    lv_obj_set_width(ui_GImageBreak0, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(ui_GImageBreak0, LV_SIZE_CONTENT);    /// 128
    lv_obj_set_align(ui_GImageBreak0, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GImageBreak0, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_GImageBreak0, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_GImageBreak180 = lv_img_create(ui_GPanelPool2);
    lv_img_set_src(ui_GImageBreak180, &ui_img_break180_png);
    lv_obj_set_width(ui_GImageBreak180, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(ui_GImageBreak180, LV_SIZE_CONTENT);    /// 128
    lv_obj_set_align(ui_GImageBreak180, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GImageBreak180, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_GImageBreak180, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	ui_PanelPool2Ply2 = ui_PanelPoolPlayer_create(ui_GPanelPool2);
	lv_obj_set_x(ui_PanelPool2Ply2, 125);
	lv_obj_set_y(ui_PanelPool2Ply2, 0);

	ui_GPanelPool3 = lv_obj_create(ui_ScreenGame);
	lv_obj_set_width(ui_GPanelPool3, 430);
	lv_obj_set_height(ui_GPanelPool3, 225);
	lv_obj_set_x(ui_GPanelPool3, 0);
	lv_obj_set_y(ui_GPanelPool3, 30);
	lv_obj_set_align(ui_GPanelPool3, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(ui_GPanelPool3, LV_OBJ_FLAG_HIDDEN);     /// Flags
	lv_obj_clear_flag(ui_GPanelPool3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_GPanelPool3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_GPanelPool3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_GPanelPool3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_PanelPool3Ply1 = ui_PanelPoolPlayer_create(ui_GPanelPool3);
	lv_obj_set_width(ui_PanelPool3Ply1, 140);
	lv_obj_set_height(ui_PanelPool3Ply1, 220);
	lv_obj_set_x(ui_PanelPool3Ply1, -145);
	lv_obj_set_y(ui_PanelPool3Ply1, 0);

	ui_PanelPool3Ply2 = ui_PanelPoolPlayer_create(ui_GPanelPool3);
	lv_obj_set_width(ui_PanelPool3Ply2, 140);
	lv_obj_set_height(ui_PanelPool3Ply2, 220);
	lv_obj_set_x(ui_PanelPool3Ply2, 0);
	lv_obj_set_y(ui_PanelPool3Ply2, 0);

	ui_PanelPool3Ply3 = ui_PanelPoolPlayer_create(ui_GPanelPool3);
	lv_obj_set_width(ui_PanelPool3Ply3, 140);
	lv_obj_set_height(ui_PanelPool3Ply3, 220);
	lv_obj_set_x(ui_PanelPool3Ply3, 145);
	lv_obj_set_y(ui_PanelPool3Ply3, 0);

	ui_MBPanelPool = lv_obj_create(ui_ScreenGame);
	lv_obj_set_width(ui_MBPanelPool, 430);
	lv_obj_set_height(ui_MBPanelPool, 225);
	lv_obj_set_x(ui_MBPanelPool, 0);
	lv_obj_set_y(ui_MBPanelPool, 30);
	lv_obj_set_align(ui_MBPanelPool, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN);     /// Flags
	lv_obj_clear_flag(ui_MBPanelPool, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBPanelPool, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBPanelPool, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_MBPanelPool, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_MBPanelPool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBLabelPoolResetQ = lv_label_create(ui_MBPanelPool);
	lv_obj_set_width(ui_MBLabelPoolResetQ, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBLabelPoolResetQ, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MBLabelPoolResetQ, 0);
	lv_obj_set_y(ui_MBLabelPoolResetQ, 35);
	lv_obj_set_align(ui_MBLabelPoolResetQ, LV_ALIGN_TOP_MID);
	lv_label_set_text(ui_MBLabelPoolResetQ, "Начать новый матч?");
	lv_obj_set_style_text_color(ui_MBLabelPoolResetQ, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_MBLabelPoolResetQ, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBBtnPoolResetYes = lv_btn_create(ui_MBPanelPool);
	lv_obj_set_width(ui_MBBtnPoolResetYes, 165);
	lv_obj_set_height(ui_MBBtnPoolResetYes, 65);
	lv_obj_set_x(ui_MBBtnPoolResetYes, -110);
	lv_obj_set_y(ui_MBBtnPoolResetYes, 60);
	lv_obj_set_align(ui_MBBtnPoolResetYes, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_MBBtnPoolResetYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_MBBtnPoolResetYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBBtnPoolResetYes, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBBtnPoolResetYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_MBBtnPoolResetYes, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBLabelPoolResetYes = lv_label_create(ui_MBBtnPoolResetYes);
	lv_obj_set_width(ui_MBLabelPoolResetYes, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBLabelPoolResetYes, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_MBLabelPoolResetYes, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MBLabelPoolResetYes, "ДА");

	ui_MBBtnPoolResetNo = lv_btn_create(ui_MBPanelPool);
	lv_obj_set_width(ui_MBBtnPoolResetNo, 165);
	lv_obj_set_height(ui_MBBtnPoolResetNo, 65);
	lv_obj_set_x(ui_MBBtnPoolResetNo, 110);
	lv_obj_set_y(ui_MBBtnPoolResetNo, 60);
	lv_obj_set_align(ui_MBBtnPoolResetNo, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_MBBtnPoolResetNo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_MBBtnPoolResetNo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBBtnPoolResetNo, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBBtnPoolResetNo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_MBBtnPoolResetNo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBLabelPoolResetNo = lv_label_create(ui_MBBtnPoolResetNo);
	lv_obj_set_width(ui_MBLabelPoolResetNo, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBLabelPoolResetNo, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_MBLabelPoolResetNo, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MBLabelPoolResetNo, "НЕТ");

	ui_NameKeyboard = ui_NameKeyboard_create(ui_ScreenGame);
    lv_obj_set_x(ui_NameKeyboard, 0);
    lv_obj_set_y(ui_NameKeyboard, 0);
}

///////////////////// EXPORT ////////////////////

void gui_game_create()
{
	ui_ScreenGame_screen_init();

	lv_obj_add_event_cb(ui_ScreenGame, ui_event_ScreenGame, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_GLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_GLabelRefresh, ui_event_onLabelReset, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_GSwitchPlyCount, ui_event_PSwitchPlyCount, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_GImageBreak0, ui_event_PImageBreak, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_GImageBreak180, ui_event_PImageBreak, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_MBBtnPoolResetYes, ui_event_MB_ResetYes, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBBtnPoolResetNo, ui_event_MB_ResetNo, LV_EVENT_ALL, NULL);
}

void changeName(lv_event_t* e)
{
	lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

	lv_obj_t* parent = comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER];

	if (parent == ui_PanelPool2Ply1)
	{
		ui_comp_set_callback(ui_NameKeyboard, ui_event_update2Ply1Name);
    	lv_textarea_set_text(ui_comp_get_child(ui_NameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), gui_getPlayerName(PLAYER1));
	}
	else if (parent == ui_PanelPool2Ply2)
	{
		ui_comp_set_callback(ui_NameKeyboard, ui_event_update2Ply2Name);
    	lv_textarea_set_text(ui_comp_get_child(ui_NameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), gui_getPlayerName(PLAYER2));
	}
	else if (parent == ui_PanelPool3Ply1)
	{
		ui_comp_set_callback(ui_NameKeyboard, ui_event_update3Ply1Name);
    	lv_textarea_set_text(ui_comp_get_child(ui_NameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), gui_getPlayerName(PLAYER_EX1));
	}
	else if (parent == ui_PanelPool3Ply2)
	{
		ui_comp_set_callback(ui_NameKeyboard, ui_event_update3Ply2Name);
    	lv_textarea_set_text(ui_comp_get_child(ui_NameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), gui_getPlayerName(PLAYER_EX2));
	}
	else if (parent == ui_PanelPool3Ply3)
	{
		ui_comp_set_callback(ui_NameKeyboard, ui_event_update3Ply3Name);
    	lv_textarea_set_text(ui_comp_get_child(ui_NameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), gui_getPlayerName(PLAYER_EX3));
	}
	else
	{
		ui_comp_set_callback(ui_NameKeyboard, NULL);
	}

	_ui_flag_modify(ui_NameKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void changeScore(lv_event_t* e)
{
	if (scoreTimer != NULL) return;

	if(gameHasSatrted == false)
	{
		_ui_flag_modify(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
		return;
	}

	lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

	_ui_flag_modify(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE], LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

	scoreTimer = lv_timer_create(ui_hideScorePlusMinus, 3000, comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE]);
}

void changeScorePlus(lv_event_t* e)
{
	ui_hideScorePlusMinus(scoreTimer);

	updateScoreInComponent((lv_obj_t**)lv_event_get_user_data(e), INCREASE);
}

void changeScoreMinus(lv_event_t* e)
{
	ui_hideScorePlusMinus(scoreTimer);

	updateScoreInComponent((lv_obj_t**)lv_event_get_user_data(e), DECREASE);
}

