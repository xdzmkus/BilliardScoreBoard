#include "gui_main.h"
#include "gui.h"
#include "gui_settings.h"
#include "gui_lottery.h"
#include "gui_game.h"
#include "gui_stream.h"
#include "gui_snooker.h"
#include "gui_darts.h"

#include "defs.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenMain;
lv_obj_t* ui_MLabelLogo;
lv_obj_t* ui_MBtnDarts;
lv_obj_t* ui_MBtnLabelDarts;
lv_obj_t* ui_MBtnLottery;
lv_obj_t* ui_MBtnLabelLottery;
lv_obj_t * ui_MBtnGame;
lv_obj_t * ui_MBtnLabelGame;
lv_obj_t * ui_MBtnStream;
lv_obj_t * ui_MBtnLabelStream;
lv_obj_t * ui_MBtnSnooker;
lv_obj_t * ui_MBtnLabelSnooker;
lv_obj_t* ui_MBtnSettings;
lv_obj_t* ui_MBtnLabelSettings;
lv_obj_t* ui_MLabelWifi;
lv_obj_t* ui_MLabelTelega;
lv_obj_t* ui_MLabelAudio;

static lv_timer_t* connectivityTimer;

///////////////////// EVENTS ////////////////////

static void ui_updateWifiState(lv_timer_t* timer)
{
	if (gui_wifiIsEnabledAndConnected())
	{
		lv_obj_clear_state(ui_MLabelWifi, LV_STATE_DISABLED);
	}
	else
	{
		lv_obj_add_state(ui_MLabelWifi, LV_STATE_DISABLED);
	}
}

static void ui_event_BtnDarts(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenDarts, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_darts_create);
	}
}
static void ui_event_BtnLottery(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenLottery, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_lottery_create);
	}
}
static void ui_event_BtnStream(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenStream, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_stream_create);
	}
}
static void ui_event_BtnGame(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenGame, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_game_create);
	}
}
static void ui_event_BtnSettings(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_settings_create);
	}
}
static void ui_event_BtnSnooker(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenSnooker, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_snooker_create);
	}
}

static void ui_event_ScreenMain(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_SCREEN_LOAD_START)
	{
		lv_label_set_text(ui_MLabelLogo, boardEEPROMdata.greeting); // show greeting message

		// set state of telegram
		boardEEPROMdata.isTelegaEnabled ? lv_obj_clear_state(ui_MLabelTelega, LV_STATE_DISABLED) : lv_obj_add_state(ui_MLabelTelega, LV_STATE_DISABLED);

		// set state of audio
		boardEEPROMdata.isAudioEnabled ? lv_obj_clear_state(ui_MLabelAudio, LV_STATE_DISABLED) : lv_obj_add_state(ui_MLabelAudio, LV_STATE_DISABLED);

		// set state of wifi
		gui_wifiIsEnabledAndConnected() ? lv_obj_clear_state(ui_MLabelWifi, LV_STATE_DISABLED) : lv_obj_add_state(ui_MLabelWifi, LV_STATE_DISABLED);

		connectivityTimer = lv_timer_create(ui_updateWifiState, 3000, NULL); // update wifi state every 3 sec
		lv_timer_set_repeat_count(connectivityTimer, -1);
	}
	else if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
	{
		if (connectivityTimer != NULL)
		{
			lv_timer_del(connectivityTimer);
			connectivityTimer = NULL;
		}
	}
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenMain_screen_init(void)
{
	ui_ScreenMain = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_image_src(ui_ScreenMain, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_ScreenMain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_ScreenMain, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MLabelLogo = lv_label_create(ui_ScreenMain);
	lv_obj_set_width(ui_MLabelLogo, 400);
	lv_obj_set_height(ui_MLabelLogo, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MLabelLogo, 0);
	lv_obj_set_y(ui_MLabelLogo, 40);
	lv_obj_set_align(ui_MLabelLogo, LV_ALIGN_TOP_MID);
	lv_label_set_long_mode(ui_MLabelLogo, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_style_text_align(ui_MLabelLogo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBtnDarts = lv_btn_create(ui_ScreenMain);
	lv_obj_set_width(ui_MBtnDarts, 190);
	lv_obj_set_height(ui_MBtnDarts, 50);
	lv_obj_set_x(ui_MBtnDarts, -100);
	lv_obj_set_y(ui_MBtnDarts, -40);
	lv_obj_set_align(ui_MBtnDarts, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBtnDarts, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBtnDarts, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBtnLabelDarts = lv_label_create(ui_MBtnDarts);
	lv_obj_set_width(ui_MBtnLabelDarts, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBtnLabelDarts, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_MBtnLabelDarts, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MBtnLabelDarts, "Дартс");

	ui_MBtnLottery = lv_btn_create(ui_ScreenMain);
	lv_obj_set_width(ui_MBtnLottery, 190);
	lv_obj_set_height(ui_MBtnLottery, 50);
	lv_obj_set_x(ui_MBtnLottery, 100);
	lv_obj_set_y(ui_MBtnLottery, -40);
	lv_obj_set_align(ui_MBtnLottery, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBtnLottery, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBtnLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBtnLabelLottery = lv_label_create(ui_MBtnLottery);
	lv_obj_set_width(ui_MBtnLabelLottery, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBtnLabelLottery, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_MBtnLabelLottery, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MBtnLabelLottery, "Жребий");

    ui_MBtnGame = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnGame, 150);
    lv_obj_set_height(ui_MBtnGame, 50);
    lv_obj_set_x(ui_MBtnGame, -120);
    lv_obj_set_y(ui_MBtnGame, 25);
    lv_obj_set_align(ui_MBtnGame, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnGame, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnGame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnGame, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelGame = lv_label_create(ui_MBtnGame);
    lv_obj_set_width(ui_MBtnLabelGame, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelGame, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelGame, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelGame, "Матч");

    ui_MBtnStream = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnStream, 50);
    lv_obj_set_height(ui_MBtnStream, 50);
    lv_obj_set_x(ui_MBtnStream, 0);
    lv_obj_set_y(ui_MBtnStream, 25);
    lv_obj_set_align(ui_MBtnStream, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnStream, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnStream, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MBtnStream, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MBtnStream, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnStream, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_MBtnStream, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_MBtnStream, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelStream = lv_label_create(ui_MBtnStream);
    lv_obj_set_width(ui_MBtnLabelStream, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelStream, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelStream, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelStream, "TV");

    ui_MBtnSnooker = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSnooker, 150);
    lv_obj_set_height(ui_MBtnSnooker, 50);
    lv_obj_set_x(ui_MBtnSnooker, 120);
    lv_obj_set_y(ui_MBtnSnooker, 25);
    lv_obj_set_align(ui_MBtnSnooker, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnSnooker, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelSnooker = lv_label_create(ui_MBtnSnooker);
    lv_obj_set_width(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelSnooker, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelSnooker, "Снукер");

	ui_MBtnSettings = lv_btn_create(ui_ScreenMain);
	lv_obj_set_width(ui_MBtnSettings, 190);
	lv_obj_set_height(ui_MBtnSettings, 50);
	lv_obj_set_x(ui_MBtnSettings, 100);
	lv_obj_set_y(ui_MBtnSettings, 90);
	lv_obj_set_align(ui_MBtnSettings, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_MBtnSettings, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(ui_MBtnSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_MBtnSettings, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MBtnSettings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MBtnLabelSettings = lv_label_create(ui_MBtnSettings);
	lv_obj_set_width(ui_MBtnLabelSettings, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MBtnLabelSettings, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_MBtnLabelSettings, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MBtnLabelSettings, "Настройки");

	ui_MLabelWifi = lv_label_create(ui_ScreenMain);
	lv_obj_set_width(ui_MLabelWifi, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MLabelWifi, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MLabelWifi, -160);
	lv_obj_set_y(ui_MLabelWifi, 90);
	lv_obj_set_align(ui_MLabelWifi, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MLabelWifi, LV_SYMBOL_WIFI);
	lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_decor(ui_MLabelWifi, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);

	ui_MLabelTelega = lv_label_create(ui_ScreenMain);
	lv_obj_set_width(ui_MLabelTelega, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MLabelTelega, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MLabelTelega, -100);
	lv_obj_set_y(ui_MLabelTelega, 90);
	lv_obj_set_align(ui_MLabelTelega, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MLabelTelega, LV_SYMBOL_TELEGRAM);
	lv_obj_set_style_text_color(ui_MLabelTelega, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_opa(ui_MLabelTelega, 255, LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_decor(ui_MLabelTelega, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);

	ui_MLabelAudio = lv_label_create(ui_ScreenMain);
	lv_obj_set_width(ui_MLabelAudio, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MLabelAudio, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MLabelAudio, -40);
	lv_obj_set_y(ui_MLabelAudio, 90);
	lv_obj_set_align(ui_MLabelAudio, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MLabelAudio, LV_SYMBOL_AUDIO);
	lv_obj_set_style_text_color(ui_MLabelAudio, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_opa(ui_MLabelAudio, 255, LV_PART_MAIN | LV_STATE_DISABLED);
	lv_obj_set_style_text_decor(ui_MLabelAudio, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);
}

///////////////////// FUNCTIONS ////////////////////

void gui_main_create(void)
{
	ui_ScreenMain_screen_init();

	lv_obj_add_event_cb(ui_MBtnDarts, ui_event_BtnDarts, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBtnLottery, ui_event_BtnLottery, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBtnStream, ui_event_BtnStream, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBtnGame, ui_event_BtnGame, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBtnSettings, ui_event_BtnSettings, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_MBtnSnooker, ui_event_BtnSnooker, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_ScreenMain, ui_event_ScreenMain, LV_EVENT_ALL, NULL);
}
