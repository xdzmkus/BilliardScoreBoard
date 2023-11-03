﻿#include "gui_main.h"
#include "gui.h"
#include "gui_snooker.h"
#include "gui_pool.h"
#include "gui_darts.h"
#include "gui_lottery.h"
#include "gui_settings.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

#include "TaskAudio.h"
#include "TaskNetwork.h"

extern char greeting[97];

volatile bool isTelegram = false;
volatile bool isAudio = false;


///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenMain;
lv_obj_t* ui_MBtnPool;
lv_obj_t* ui_MBtnLabelPool;
lv_obj_t* ui_MBtnSnooker;
lv_obj_t* ui_MBtnLabelSnooker;
lv_obj_t* ui_MBtnDarts;
lv_obj_t* ui_MBtnLabelDarts;
lv_obj_t* ui_MBtnLottery;
lv_obj_t* ui_MBtnLabelLottery;
lv_obj_t* ui_MBtnSettings;
lv_obj_t* ui_MBtnLabelSettings;
lv_obj_t* ui_MLabelLogo;
lv_obj_t* ui_MButtonAP;
lv_obj_t* ui_MLabelAP;
lv_obj_t* ui_MButtonWifi;
lv_obj_t* ui_MLabelWifi;
lv_obj_t* ui_MButtonTelegram;
lv_obj_t* ui_MLabelTelegram;
lv_obj_t* ui_MButtonMedical;
lv_obj_t* ui_MLabelMedical;
lv_obj_t* ui_MButtonAudio;
lv_obj_t* ui_MLabelAudio;

static lv_timer_t* connectivityTimer;

///////////////////// FUNCTIONS ////////////////////

static void activateTelegram()
{
    isTelegram = true;

    lv_obj_add_state(ui_MButtonTelegram, LV_STATE_CHECKED);
}

static void deactivateTelegram()
{
    isTelegram = false;

    lv_obj_clear_state(ui_MButtonTelegram, LV_STATE_CHECKED);
}

static void activateAudio()
{
    isAudio = true;

    audio_turnOn();

    lv_obj_add_state(ui_MButtonAudio, LV_STATE_CHECKED);
}

static void deactivateAudio()
{
    audio_turnOff();

    isAudio = false;

    lv_obj_clear_state(ui_MButtonAudio, LV_STATE_CHECKED);
}

///////////////////// EVENTS ////////////////////

static void ui_updateButtons(lv_timer_t* timer)
{
    if (isConfigPortalStarted())
    {
        lv_obj_add_state(ui_MButtonAP, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_MButtonAP, LV_STATE_CHECKED);
    }

    if (isWifiConnected())
    {
        lv_obj_add_state(ui_MLabelWifi, LV_STATE_USER_1);
    }
    else
    {
        lv_obj_clear_state(ui_MLabelWifi, LV_STATE_USER_1);
    }

    if (isWaitingHistory())
    {
        lv_obj_add_state(ui_MButtonMedical, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_MButtonMedical, LV_STATE_CHECKED);
    }
}

static void ui_event_BtnPool(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_pool_create();

        _ui_screen_change(ui_ScreenPool, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}
static void ui_event_BtnSnooker(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_snooker_create();

        _ui_screen_change(ui_ScreenSnooker, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}
static void ui_event_BtnDarts(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_darts_create();

        _ui_screen_change(ui_ScreenDarts, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}
static void ui_event_BtnLottery(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_lottery_create();

        _ui_screen_change(ui_ScreenLottery, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}
static void ui_event_BtnSettings(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    }
}
static void ui_event_BtnAP(lv_event_t* e)
{
    lv_obj_t* target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        startConfigPortal();
    }
    else
    {
        stopConfigPortal();
    }
}
static void ui_event_BtnWiFi(lv_event_t* e)
{
    lv_obj_t* target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        startWiFi();
    }
    else
    {
        stopWiFi();
    }
}
static void ui_event_BtnMedical(lv_event_t* e)
{
    lv_obj_t* target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        subscribeHistory();
    }
    else
    {
        revokeHistory();
    }
}
static void ui_event_BtnTelegram(lv_event_t* e)
{
    lv_obj_t* target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        activateTelegram();
        deactivateAudio();
    }
    else
    {
        deactivateTelegram();
    }
}
static void ui_event_BtnAudio(lv_event_t* e)
{
    lv_obj_t* target = lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        activateAudio();
        deactivateTelegram();
    }
    else
    {
        deactivateAudio();
    }
}

static void ui_event_ScreenMain(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        lv_label_set_text(ui_MLabelLogo, greeting);

        connectivityTimer = lv_timer_create(ui_updateButtons, 3000, NULL);

        lv_timer_set_repeat_count(connectivityTimer, -1);

        ui_updateButtons(NULL);

        if (gui_isAudioDisabled())
        {
            lv_obj_add_state(ui_MButtonAudio, LV_STATE_DISABLED);
        }

        if (isTelegram)
        {
            lv_obj_add_state(ui_MButtonTelegram, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(ui_MButtonTelegram, LV_STATE_CHECKED);
        }

        if (isAudio)
        {
            lv_obj_add_state(ui_MButtonAudio, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(ui_MButtonAudio, LV_STATE_CHECKED);
        }
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
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenMain, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenMain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenMain, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnPool = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnPool, 90);
    lv_obj_set_height(ui_MBtnPool, 50);
    lv_obj_set_x(ui_MBtnPool, -135);
    lv_obj_set_y(ui_MBtnPool, 25);
    lv_obj_set_align(ui_MBtnPool, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnPool, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MBtnPool, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MBtnPool, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnPool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelPool = lv_label_create(ui_MBtnPool);
    lv_obj_set_width(ui_MBtnLabelPool, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MBtnLabelPool, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MBtnLabelPool, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelPool, "МАТЧ");

    ui_MBtnSnooker = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSnooker, 130);
    lv_obj_set_height(ui_MBtnSnooker, 50);
    lv_obj_set_x(ui_MBtnSnooker, 0);
    lv_obj_set_y(ui_MBtnSnooker, 25);
    lv_obj_set_align(ui_MBtnSnooker, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MBtnSnooker, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelSnooker = lv_label_create(ui_MBtnSnooker);
    lv_obj_set_width(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MBtnLabelSnooker, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelSnooker, "СНУКЕР");

    ui_MBtnDarts = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnDarts, 90);
    lv_obj_set_height(ui_MBtnDarts, 50);
    lv_obj_set_x(ui_MBtnDarts, 135);
    lv_obj_set_y(ui_MBtnDarts, 25);
    lv_obj_set_align(ui_MBtnDarts, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MBtnDarts, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnDarts, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelDarts = lv_label_create(ui_MBtnDarts);
    lv_obj_set_width(ui_MBtnLabelDarts, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MBtnLabelDarts, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MBtnLabelDarts, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelDarts, "ДАРТС");

    ui_MBtnLottery = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnLottery, 195);
    lv_obj_set_height(ui_MBtnLottery, 50);
    lv_obj_set_x(ui_MBtnLottery, 80);
    lv_obj_set_y(ui_MBtnLottery, -45);
    lv_obj_set_align(ui_MBtnLottery, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MBtnLottery, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelLottery = lv_label_create(ui_MBtnLottery);
    lv_obj_set_width(ui_MBtnLabelLottery, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MBtnLabelLottery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MBtnLabelLottery, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelLottery, LV_SYMBOL_SHUFFLE "  Жеребьевка");

    ui_MBtnSettings = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSettings, 150);
    lv_obj_set_height(ui_MBtnSettings, 50);
    lv_obj_set_x(ui_MBtnSettings, -105);
    lv_obj_set_y(ui_MBtnSettings, -45);
    lv_obj_set_align(ui_MBtnSettings, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnSettings, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MBtnSettings, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MBtnSettings, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnSettings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelSettings = lv_label_create(ui_MBtnSettings);
    lv_obj_set_width(ui_MBtnLabelSettings, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MBtnLabelSettings, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MBtnLabelSettings, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelSettings, LV_SYMBOL_SETTINGS " Игроки");

    ui_MLabelLogo = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelLogo, 400);
    lv_obj_set_height(ui_MLabelLogo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_MLabelLogo, 0);
    lv_obj_set_y(ui_MLabelLogo, 40);
    lv_obj_set_align(ui_MLabelLogo, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_MLabelLogo, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_MLabelLogo, "https://t.me");
    lv_obj_set_style_text_align(ui_MLabelLogo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MButtonAP = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonAP, 50);
    lv_obj_set_height(ui_MButtonAP, 50);
    lv_obj_set_x(ui_MButtonAP, -155);
    lv_obj_set_y(ui_MButtonAP, -40);
    lv_obj_set_align(ui_MButtonAP, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonAP, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MButtonAP, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MButtonAP, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonAP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelAP = lv_label_create(ui_MButtonAP);
    lv_obj_set_width(ui_MLabelAP, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MLabelAP, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MLabelAP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelAP, LV_SYMBOL_AP);

    ui_MButtonWifi = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonWifi, 50);
    lv_obj_set_height(ui_MButtonWifi, 50);
    lv_obj_set_x(ui_MButtonWifi, 0);
    lv_obj_set_y(ui_MButtonWifi, -40);
    lv_obj_set_align(ui_MButtonWifi, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_state(ui_MButtonWifi, LV_STATE_CHECKED);     /// States
    lv_obj_add_flag(ui_MButtonWifi, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MButtonWifi, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MButtonWifi, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelWifi = lv_label_create(ui_MButtonWifi);
    lv_obj_set_width(ui_MLabelWifi, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MLabelWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MLabelWifi, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelWifi, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_USER_1);
    lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_USER_1);

    ui_MButtonTelegram = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonTelegram, 50);
    lv_obj_set_height(ui_MButtonTelegram, 50);
    lv_obj_set_x(ui_MButtonTelegram, 80);
    lv_obj_set_y(ui_MButtonTelegram, -40);
    lv_obj_set_align(ui_MButtonTelegram, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonTelegram, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MButtonTelegram, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MButtonTelegram, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonTelegram, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelTelegram = lv_label_create(ui_MButtonTelegram);
    lv_obj_set_width(ui_MLabelTelegram, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MLabelTelegram, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MLabelTelegram, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelTelegram, LV_SYMBOL_TELEGRAM);

    ui_MButtonMedical = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonMedical, 50);
    lv_obj_set_height(ui_MButtonMedical, 50);
    lv_obj_set_x(ui_MButtonMedical, -80);
    lv_obj_set_y(ui_MButtonMedical, -40);
    lv_obj_set_align(ui_MButtonMedical, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonMedical, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MButtonMedical, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MButtonMedical, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonMedical, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelMedical = lv_label_create(ui_MButtonMedical);
    lv_obj_set_width(ui_MLabelMedical, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MLabelMedical, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MLabelMedical, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelMedical, LV_SYMBOL_MEDICAL);

    ui_MButtonAudio = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonAudio, 50);
    lv_obj_set_height(ui_MButtonAudio, 50);
    lv_obj_set_x(ui_MButtonAudio, 155);
    lv_obj_set_y(ui_MButtonAudio, -40);
    lv_obj_set_align(ui_MButtonAudio, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonAudio, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_MButtonAudio, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_MButtonAudio, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonAudio, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelAudio = lv_label_create(ui_MButtonAudio);
    lv_obj_set_width(ui_MLabelAudio, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MLabelAudio, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_MLabelAudio, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelAudio, LV_SYMBOL_AUDIO);

}

///////////////////// EXPORT ////////////////////

void gui_main_create(void)
{
    ui_ScreenMain_screen_init();
    
    lv_obj_add_event_cb(ui_MBtnPool, ui_event_BtnPool, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnSnooker, ui_event_BtnSnooker, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnDarts, ui_event_BtnDarts, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnLottery, ui_event_BtnLottery, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnSettings, ui_event_BtnSettings, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MButtonAP, ui_event_BtnAP, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonWifi, ui_event_BtnWiFi, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonMedical, ui_event_BtnMedical, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonTelegram, ui_event_BtnTelegram, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonAudio, ui_event_BtnAudio, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_event_cb(ui_ScreenMain, ui_event_ScreenMain, LV_EVENT_ALL, NULL);
}

void gui_main_delete()
{
    if (ui_ScreenMain == NULL) return;

    if (connectivityTimer != NULL)
    {
        lv_timer_del(connectivityTimer);
        connectivityTimer = NULL;
    }

    lv_obj_del(ui_ScreenMain);
    ui_ScreenMain = NULL;
}
