#include "gui_main.h"
#include "gui_snooker.h"
#include "gui_pool.h"
#include "gui_lottery.h"
#include "gui_settings.h"
#include "gui.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

#include "WiFi.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t* ui_ScreenMain;
lv_obj_t* ui_MBtnPool;
lv_obj_t* ui_MBtnLabelPool;
lv_obj_t* ui_MBtnSnooker;
lv_obj_t* ui_MBtnLabelSnooker;
lv_obj_t* ui_MBtnLottery;
lv_obj_t* ui_MBtnLabelLottery;
lv_obj_t* ui_MBtnSettings;
lv_obj_t* ui_MBtnLabelSettings;
lv_obj_t* ui_MLabelLogo;
lv_obj_t* ui_MLabelDate;
lv_obj_t* ui_MLabelTime;
lv_obj_t* ui_MButtonTimeReset;
lv_obj_t* ui_MLabelTimeReset;
lv_obj_t* ui_MButtonAP;
lv_obj_t* ui_MLabelAP;
lv_obj_t* ui_MButtonWifi;
lv_obj_t* ui_MLabelWifi;
lv_obj_t* ui_MButtonTelegram;
lv_obj_t* ui_MLabelTelegram;
lv_obj_t* ui_MButtonMedical;
lv_obj_t* ui_MLabelMedical;

static uint32_t secondsPassed = 0;

extern volatile bool sendMedicalRequest;

extern void stopConfigPortal();
extern void startConfigPortal();
extern void startWiFi();
extern void stopWiFi();

///////////////////// FUNCTIONS ////////////////////
static void ui_event_BtnPool(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenPool, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}
static void ui_event_BtnSnooker(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenSnooker, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}
static void ui_event_BtnLottery(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenLottery, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}
static void ui_event_BtnSettings(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}
static void ui_event_ResetTime(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        secondsPassed = 0;
        _ui_label_set_property(ui_MLabelTime, _UI_LABEL_PROPERTY_TEXT, "0:00:00");
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
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        sendMedicalRequest = true;
    }
}

///////////////////// SCREENS ////////////////////
void ui_ScreenMain_screen_init(void)
{
    ui_ScreenMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenMain, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenMain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenMain, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnPool = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnPool, 160);
    lv_obj_set_height(ui_MBtnPool, 50);
    lv_obj_set_x(ui_MBtnPool, -100);
    lv_obj_set_y(ui_MBtnPool, -20);
    lv_obj_set_align(ui_MBtnPool, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnPool, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnPool, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnPool, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnPool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelPool = lv_label_create(ui_MBtnPool);
    lv_obj_set_width(ui_MBtnLabelPool, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelPool, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelPool, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelPool, "МАТЧ");

    ui_MBtnSnooker = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSnooker, 160);
    lv_obj_set_height(ui_MBtnSnooker, 50);
    lv_obj_set_x(ui_MBtnSnooker, 100);
    lv_obj_set_y(ui_MBtnSnooker, -20);
    lv_obj_set_align(ui_MBtnSnooker, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnSnooker, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelSnooker = lv_label_create(ui_MBtnSnooker);
    lv_obj_set_width(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelSnooker, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelSnooker, "СНУКЕР");

    ui_MBtnLottery = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnLottery, 160);
    lv_obj_set_height(ui_MBtnLottery, 50);
    lv_obj_set_x(ui_MBtnLottery, -100);
    lv_obj_set_y(ui_MBtnLottery, 40);
    lv_obj_set_align(ui_MBtnLottery, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnLottery, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelLottery = lv_label_create(ui_MBtnLottery);
    lv_obj_set_width(ui_MBtnLabelLottery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelLottery, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelLottery, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelLottery, "Жеребьевка");

    ui_MBtnSettings = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSettings, 160);
    lv_obj_set_height(ui_MBtnSettings, 50);
    lv_obj_set_x(ui_MBtnSettings, 100);
    lv_obj_set_y(ui_MBtnSettings, 40);
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

    ui_MLabelLogo = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelLogo, 400);
    lv_obj_set_height(ui_MLabelLogo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelLogo, 0);
    lv_obj_set_y(ui_MLabelLogo, 30);
    lv_obj_set_align(ui_MLabelLogo, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_MLabelLogo, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_MLabelLogo, "Г Е Н К А");
    lv_obj_set_style_text_align(ui_MLabelLogo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelDate = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelDate, 160);
    lv_obj_set_height(ui_MLabelDate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelDate, 60);
    lv_obj_set_y(ui_MLabelDate, 70);
    lv_label_set_text(ui_MLabelDate, "01/04 23:59");
    lv_obj_set_style_text_align(ui_MLabelDate, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelTime = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelTime, 100);
    lv_obj_set_height(ui_MLabelTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelTime, -110);
    lv_obj_set_y(ui_MLabelTime, 70);
    lv_obj_set_align(ui_MLabelTime, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_MLabelTime, "0:00:00");
    lv_obj_set_style_text_align(ui_MLabelTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MButtonTimeReset = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonTimeReset, 35);
    lv_obj_set_height(ui_MButtonTimeReset, 35);
    lv_obj_set_x(ui_MButtonTimeReset, -70);
    lv_obj_set_y(ui_MButtonTimeReset, 68);
    lv_obj_set_align(ui_MButtonTimeReset, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_MButtonTimeReset, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MButtonTimeReset, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MButtonTimeReset, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonTimeReset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelTimeReset = lv_label_create(ui_MButtonTimeReset);
    lv_obj_set_width(ui_MLabelTimeReset, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelTimeReset, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MLabelTimeReset, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelTimeReset, LV_SYMBOL_REFRESH);

    ui_MButtonAP = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonAP, 50);
    lv_obj_set_height(ui_MButtonAP, 50);
    lv_obj_set_x(ui_MButtonAP, -140);
    lv_obj_set_y(ui_MButtonAP, -35);
    lv_obj_set_align(ui_MButtonAP, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonAP, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MButtonAP, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MButtonAP, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonAP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelAP = lv_label_create(ui_MButtonAP);
    lv_obj_set_width(ui_MLabelAP, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelAP, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MLabelAP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelAP, LV_SYMBOL_AP);

    ui_MButtonWifi = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonWifi, 50);
    lv_obj_set_height(ui_MButtonWifi, 50);
    lv_obj_set_x(ui_MButtonWifi, -60);
    lv_obj_set_y(ui_MButtonWifi, -35);
    lv_obj_set_align(ui_MButtonWifi, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonWifi, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MButtonWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MButtonWifi, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelWifi = lv_label_create(ui_MButtonWifi);
    lv_obj_set_width(ui_MLabelWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MLabelWifi, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelWifi, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_USER_1);
    lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_USER_1);

    ui_MButtonTelegram = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonTelegram, 50);
    lv_obj_set_height(ui_MButtonTelegram, 50);
    lv_obj_set_x(ui_MButtonTelegram, 60);
    lv_obj_set_y(ui_MButtonTelegram, -35);
    lv_obj_set_align(ui_MButtonTelegram, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonTelegram, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MButtonTelegram, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MButtonTelegram, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonTelegram, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelTelegram = lv_label_create(ui_MButtonTelegram);
    lv_obj_set_width(ui_MLabelTelegram, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelTelegram, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MLabelTelegram, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelTelegram, LV_SYMBOL_TELEGRAM);

    ui_MButtonMedical = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MButtonMedical, 50);
    lv_obj_set_height(ui_MButtonMedical, 50);
    lv_obj_set_x(ui_MButtonMedical, 140);
    lv_obj_set_y(ui_MButtonMedical, -35);
    lv_obj_set_align(ui_MButtonMedical, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_MButtonMedical, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MButtonMedical, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MButtonMedical, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MButtonMedical, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelMedical = lv_label_create(ui_MButtonMedical);
    lv_obj_set_width(ui_MLabelMedical, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelMedical, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MLabelMedical, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelMedical, LV_SYMBOL_MEDICAL);

}

void gui_main_init(void)
{
    ui_ScreenMain_screen_init();

    lv_obj_add_event_cb(ui_MBtnPool, ui_event_BtnPool, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnSnooker, ui_event_BtnSnooker, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnLottery, ui_event_BtnLottery, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBtnSettings, ui_event_BtnSettings, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MButtonTimeReset, ui_event_ResetTime, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MButtonAP, ui_event_BtnAP, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonWifi, ui_event_BtnWiFi, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_MButtonMedical, ui_event_BtnMedical, LV_EVENT_ALL, NULL);
}

void gui_main_updateTime()
{
    // Update match time:

    ++secondsPassed;

    char passedTime[] = "00:00:00";

    uint8_t h = secondsPassed / 3600;
    uint8_t m = (secondsPassed - h * 3600) / 60;
    uint8_t s = secondsPassed % 60;

    sprintf(passedTime, "%2hu:%02hu:%02hu", h, m, s);

    _ui_label_set_property(ui_MLabelTime, _UI_LABEL_PROPERTY_TEXT, passedTime);

    // Update date and time:

    char date[] = "DD/MM hh:mm";

    lv_snprintf(date, sizeof(date), "%02d/%02d %02d:%02d", gui_date_day, gui_date_month, gui_time_hours, gui_time_minutes);

    if (strcmp(lv_label_get_text(ui_MLabelDate), date) != 0)
    {
        lv_label_set_text(ui_MLabelDate, date);
    }
}

void gui_main_updateAP(bool started)
{
    if (started)
    {
        lv_obj_add_state(ui_MButtonAP, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_MButtonAP, LV_STATE_CHECKED);
    }
    
    lv_obj_invalidate(ui_MButtonAP);
}

void gui_main_updateWiFi(bool connected)
{
    if (connected)
    {
        lv_obj_add_state(ui_MLabelWifi, LV_STATE_USER_1);
    }
    else
    {
        lv_obj_clear_state(ui_MLabelWifi, LV_STATE_USER_1);
    }

    lv_obj_invalidate(ui_MButtonWifi);
}

bool gui_main_isTelegram()
{
    return lv_obj_has_state(ui_MButtonTelegram, LV_STATE_CHECKED);
}
