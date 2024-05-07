#include "gui_lottery.h"
#include "gui_main.h"
#include "gui.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenLottery;
lv_obj_t* ui_LRollerLots;
lv_obj_t* ui_LPanelLot;
lv_obj_t* ui_LLabelLot;
lv_obj_t* ui_LPanelLottery;
lv_obj_t* ui_LLabelLottery;
lv_obj_t* ui_LPanelListLots;
lv_obj_t* ui_LLabelListLots;
lv_obj_t* ui_LLabelHome;
lv_obj_t* ui_LLabelRefresh;

static lv_timer_t* lotTimer;

///////////////////// ACTIONS ////////////////////

#define MAX_LOTS 32

static uint8_t lotCount = 2;
static uint8_t lots[MAX_LOTS] = { 0 };
static bool lotMask[MAX_LOTS] = { false };

static void showLotsList()
{
	String listLots;

	for (uint8_t i = 0; i < MAX_LOTS; i++)
	{
		if (lots[i] == 0) break;
		listLots += lots[i];
		listLots += "\n";
	}

	_ui_label_set_property(ui_LLabelListLots, _UI_LABEL_PROPERTY_TEXT, listLots.c_str());

	lv_obj_scroll_to_y(ui_LPanelListLots, lv_obj_get_height(ui_LLabelListLots), LV_ANIM_OFF);
}

static void saveLot(lv_timer_t* timer)
{
	_ui_flag_modify(ui_LPanelLottery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	_ui_flag_modify(ui_LPanelLot, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

	showLotsList();

	lv_timer_del(lotTimer);
	lotTimer = NULL;
}

static void clearLottery(lv_event_t* e)
{
	if (lotTimer != NULL)
	{
		lv_timer_del(lotTimer);
		lotTimer = NULL;
	}

	for (uint8_t i = 0; i < MAX_LOTS; i++)
	{
		lotMask[i] = false;
		lots[i] = 0;
	}

	_ui_flag_modify(ui_LPanelLot, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
	_ui_flag_modify(ui_LPanelLottery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

	_ui_label_set_property(ui_LLabelListLots, _UI_LABEL_PROPERTY_TEXT, "");
	_ui_label_set_property(ui_LLabelLot, _UI_LABEL_PROPERTY_TEXT, "");
}

static void pullLottery(lv_event_t* e)
{
	_ui_flag_modify(ui_LPanelLot, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
	_ui_flag_modify(ui_LPanelLottery, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

	srandom(millis());

	for (uint16_t x = 0; x < MAX_LOTS * 1000; ++x)
	{
		uint8_t rLot = rand() % lotCount;

		if (lotMask[rLot] == true)	continue;

		lotMask[rLot] = true;

		++rLot; // human visible value

		// save pulled lot in vector
		for (uint8_t i = 0; i < MAX_LOTS; i++)
		{
			if (lots[i] == 0)
			{
				lots[i] = rLot;
				break;
			}
		}

		// show pulled lot
		lv_label_set_text_fmt(ui_LLabelLot, "%1d", rLot);

		gui_sayLot(rLot);

		lotTimer = lv_timer_create(saveLot, 2000, NULL);

		return;
	}

	lv_label_set_text(ui_LLabelLot, "-");
}

///////////////////// FUNCTIONS ////////////////////

static void ui_event_RollerLots(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_VALUE_CHANGED)
	{
		lotCount = lv_roller_get_selected(ui_LRollerLots) + 2;

		clearLottery(e);
	}
}

static void ui_event_PanelLottery(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		pullLottery(e);
	}
}

static void ui_event_onLabelHome(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		_ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_main_create);
	}
}

static void ui_event_onLabelRefresh(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_CLICKED)
	{
		clearLottery(e);
	}
}

static void ui_event_ScreenLottery(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (event_code == LV_EVENT_SCREEN_LOADED)
	{
		lv_roller_set_selected(ui_LRollerLots, lotCount - 2, LV_ANIM_OFF);

		showLotsList();
	}
	else if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
	{
		if (lotTimer != NULL)
		{
			lv_timer_del(lotTimer);
			lotTimer = NULL;
		}
	}
}

///////////////////// SCREENS ////////////////////

void ui_ScreenLottery_screen_init(void)
{
	ui_ScreenLottery = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_ScreenLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_image_src(ui_ScreenLottery, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_ScreenLottery, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_ScreenLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_ScreenLottery, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_ScreenLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_ScreenLottery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_ScreenLottery, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LLabelHome = lv_label_create(ui_ScreenLottery);
	lv_obj_set_width(ui_LLabelHome, 120);
	lv_obj_set_height(ui_LLabelHome, 50);
	lv_obj_set_x(ui_LLabelHome, -145);
	lv_obj_set_y(ui_LLabelHome, 125);
	lv_obj_set_align(ui_LLabelHome, LV_ALIGN_CENTER);
	lv_label_set_text(ui_LLabelHome, LV_SYMBOL_HOME " Назад");
	lv_obj_add_flag(ui_LLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_LLabelHome, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LLabelRefresh = lv_label_create(ui_ScreenLottery);
	lv_obj_set_width(ui_LLabelRefresh, 150);
	lv_obj_set_height(ui_LLabelRefresh, 50);
	lv_obj_set_x(ui_LLabelRefresh, 130);
	lv_obj_set_y(ui_LLabelRefresh, 125);
	lv_obj_set_align(ui_LLabelRefresh, LV_ALIGN_CENTER);
	lv_label_set_text(ui_LLabelRefresh, "Сбросить " LV_SYMBOL_REFRESH);
	lv_obj_add_flag(ui_LLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_set_style_text_align(ui_LLabelRefresh, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LRollerLots = lv_roller_create(ui_ScreenLottery);
	lv_roller_set_options(ui_LRollerLots,
		"2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32",
		LV_ROLLER_MODE_NORMAL);
	lv_obj_set_height(ui_LRollerLots, 200);
	lv_obj_set_width(ui_LRollerLots, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(ui_LRollerLots, -175);
	lv_obj_set_y(ui_LRollerLots, -15);
	lv_obj_set_align(ui_LRollerLots, LV_ALIGN_CENTER);
	lv_obj_set_style_bg_color(ui_LRollerLots, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_LRollerLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_LRollerLots, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_LRollerLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(ui_LRollerLots, lv_color_hex(0x109108), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_LRollerLots, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

	ui_LPanelLot = lv_obj_create(ui_ScreenLottery);
	lv_obj_set_width(ui_LPanelLot, 280);
	lv_obj_set_height(ui_LPanelLot, 200);
	lv_obj_set_x(ui_LPanelLot, 0);
	lv_obj_set_y(ui_LPanelLot, -15);
	lv_obj_set_align(ui_LPanelLot, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_LPanelLot, LV_OBJ_FLAG_HIDDEN);     /// Flags
	lv_obj_clear_flag(ui_LPanelLot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_LPanelLot, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_LPanelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_LPanelLot, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_LPanelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LLabelLot = lv_label_create(ui_LPanelLot);
	lv_obj_set_width(ui_LLabelLot, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_LLabelLot, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_LLabelLot, LV_ALIGN_CENTER);
	lv_label_set_text(ui_LLabelLot, "");
	lv_obj_set_style_text_color(ui_LLabelLot, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_LLabelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_LLabelLot, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LPanelLottery = lv_obj_create(ui_ScreenLottery);
	lv_obj_set_width(ui_LPanelLottery, 280);
	lv_obj_set_height(ui_LPanelLottery, 200);
	lv_obj_set_x(ui_LPanelLottery, 0);
	lv_obj_set_y(ui_LPanelLottery, -15);
	lv_obj_set_align(ui_LPanelLottery, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_LPanelLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_bg_color(ui_LPanelLottery, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_LPanelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_LPanelLottery, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_LPanelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LLabelLottery = lv_label_create(ui_LPanelLottery);
	lv_obj_set_width(ui_LLabelLottery, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_LLabelLottery, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_LLabelLottery, LV_ALIGN_CENTER);
	lv_label_set_text(ui_LLabelLottery, "Тянуть жребий");
	lv_obj_set_style_text_color(ui_LLabelLottery, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_LLabelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LPanelListLots = lv_obj_create(ui_ScreenLottery);
	lv_obj_set_width(ui_LPanelListLots, 65);
	lv_obj_set_height(ui_LPanelListLots, 200);
	lv_obj_set_x(ui_LPanelListLots, 175);
	lv_obj_set_y(ui_LPanelListLots, -15);
	lv_obj_set_align(ui_LPanelListLots, LV_ALIGN_CENTER);
	lv_obj_set_style_bg_color(ui_LPanelListLots, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_LPanelListLots, lv_color_hex(0x625020), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_LPanelListLots, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_LLabelListLots = lv_label_create(ui_LPanelListLots);
	lv_obj_set_width(ui_LLabelListLots, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_LLabelListLots, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_LLabelListLots, LV_ALIGN_TOP_MID);
	lv_label_set_text(ui_LLabelListLots, "");
	lv_obj_add_flag(ui_LLabelListLots, LV_OBJ_FLAG_CLICKABLE);     /// Flags

}

void gui_lottery_create()
{
	ui_ScreenLottery_screen_init();

	lv_obj_add_event_cb(ui_LRollerLots, ui_event_RollerLots, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_LPanelLottery, ui_event_PanelLottery, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_LLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_LLabelRefresh, ui_event_onLabelRefresh, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_ScreenLottery, ui_event_ScreenLottery, LV_EVENT_ALL, NULL);
}
