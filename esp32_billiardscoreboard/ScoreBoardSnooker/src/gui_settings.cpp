#include "gui_settings.h"
#include "gui.h"
#include "gui_components.h"
#include "gui_main.h"
#include "gui_pool.h"
#include "gui_snooker.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

extern void stopDiagnostic();
extern void startDiagnostic();
extern void stopConfigPortal();
extern void startConfigPortal();
extern void saveEEPROMGreeting(const char* msg);

lv_obj_t* ui_ScreenSettings;
lv_obj_t* ui_SPanelSettings;
lv_obj_t* ui_SPanelConnect;
lv_obj_t* ui_SLabelConnect;
lv_obj_t* ui_SLabelTelega;
lv_obj_t* ui_SSwitchTelega;
lv_obj_t* ui_SLabelAP;
lv_obj_t* ui_SSwitchAP;
lv_obj_t* ui_SLabelInsight;
lv_obj_t* ui_SSwitchInsight;
lv_obj_t* ui_SPanelPoolPlayers;
lv_obj_t* ui_SLabelPlayers;
lv_obj_t* ui_SPanelPly1;
lv_obj_t* ui_SLabelNumberPly1;
lv_obj_t* ui_SLabelNamePly1;
lv_obj_t* ui_SButtonEditPly1;
lv_obj_t* ui_SLabelEditPly1;
lv_obj_t* ui_SPanelPly2;
lv_obj_t* ui_SLabelNumberPly2;
lv_obj_t* ui_SLabelNamePly2;
lv_obj_t* ui_SButtonEditPly2;
lv_obj_t* ui_SLabelEditPly2;
lv_obj_t* ui_SPanelPly3;
lv_obj_t* ui_SLabelNumberPly3;
lv_obj_t* ui_SLabelNamePly3;
lv_obj_t* ui_SButtonEditPly3;
lv_obj_t* ui_SLabelEditPly3;
lv_obj_t* ui_SButtonPlayerSave;
lv_obj_t* ui_SLabelPlayerSave;
lv_obj_t* ui_SPanelSnooker;
lv_obj_t* ui_SLabelSnooker;
lv_obj_t* ui_SLabel6Red;
lv_obj_t* ui_SSwitch6Red;
lv_obj_t* ui_SLabelHandicap1;
lv_obj_t* ui_STextAreaHandicap1;
lv_obj_t* ui_SLabelHandicap2;
lv_obj_t* ui_STextAreaHandicap2;
lv_obj_t* ui_SButtonSnookerSave;
lv_obj_t* ui_SLabelSnookerSave;
lv_obj_t* ui_SPanelDateTime;
lv_obj_t* ui_SLabelDate;
lv_obj_t* ui_STextAreaDate;
lv_obj_t* ui_SLabelTime;
lv_obj_t* ui_SRollerHours;
lv_obj_t* ui_SLabelTimeDots;
lv_obj_t* ui_SRollerMinutes;
lv_obj_t* ui_SButtonTimeSave;
lv_obj_t* ui_SLabelTimeSave;
lv_obj_t* ui_SPanelWelcome;
lv_obj_t* ui_SLabelWelcome;
lv_obj_t* ui_SLabelGreeting;
lv_obj_t* ui_SButtonEditGreeting;
lv_obj_t* ui_SLabelEditGreeting;
lv_obj_t* ui_SButtonSaveGreeting;
lv_obj_t* ui_SLabelSaveGreeting;
lv_obj_t* ui_SLabelHome;
lv_obj_t* ui_SLabelRefresh;
lv_obj_t* ui_SNameKeyboard;


static lv_calendar_date_t gui_date;

///////////////////// FUNCTIONS ////////////////////

static void ui_refresh_DateTime()
{
    gui_date.day = gui_date_day;
    gui_date.month = gui_date_month;
    gui_date.year = gui_date_year;

    char str_date[11];
    lv_snprintf(str_date, sizeof(str_date), "%02d.%02d.%d", gui_date.day, gui_date.month, gui_date.year);
    lv_textarea_set_text(ui_STextAreaDate, str_date);

    lv_roller_set_selected(ui_SRollerHours, gui_time_hours, LV_ANIM_OFF);
    lv_roller_set_selected(ui_SRollerMinutes, gui_time_minutes, LV_ANIM_OFF);
}

static void ui_event_onDateUpdate(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    lv_obj_t* obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_calendar_get_pressed_date(obj, &gui_date);

        char str_date[11];
        lv_snprintf(str_date, sizeof(str_date), "%02d.%02d.%d", gui_date.day, gui_date.month, gui_date.year);
        lv_textarea_set_text(ta, str_date);

        lv_obj_del(obj);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
    }
}

static void ui_event_onDateChange(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);

    if (code == LV_EVENT_FOCUSED)
    {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_t* ui_SCalendar = lv_calendar_create(lv_layer_top());
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_50, 0);
        lv_obj_set_style_bg_color(lv_layer_top(), lv_palette_main(LV_PALETTE_GREY), 0);
        lv_calendar_set_today_date(ui_SCalendar, gui_date.year, gui_date.month, gui_date.day);
        lv_calendar_set_showed_date(ui_SCalendar, gui_date.year, gui_date.month);
        lv_calendar_header_arrow_create(ui_SCalendar);
        lv_obj_set_width(ui_SCalendar, lv_pct(93));
        lv_obj_set_height(ui_SCalendar, lv_pct(93));
        lv_obj_set_align(ui_SCalendar, LV_ALIGN_CENTER);
        lv_obj_add_event_cb(ui_SCalendar, ui_event_onDateUpdate, LV_EVENT_ALL, ta);
        lv_calendar_header_dropdown_create(ui_SCalendar);
    }
}

static void ui_event_onDateTimeSave(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        gui_date_day = gui_date.day;
        gui_date_month = gui_date.month;
        gui_date_year = gui_date.year;

        gui_time_hours = lv_roller_get_selected(ui_SRollerHours);
        gui_time_minutes = lv_roller_get_selected(ui_SRollerMinutes);

        gui_rtc_save = true;
    }
}

static void ui_event_onHandicapUpdate(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    lv_obj_t* kb = static_cast<lv_obj_t *>(lv_event_get_user_data(e));

    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
        lv_obj_update_layout(ui_SPanelSettings);   /*Be sure the sizes are recalculated*/
        lv_obj_set_height(ui_SPanelSettings, lv_pct(50));
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
    }
    else if (code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(ui_SPanelSettings, lv_pct(70));
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
 //       lv_indev_reset(NULL, ta);
    }
    else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_set_height(ui_SPanelSettings, lv_pct(70));
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
 //       lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
    }
}

static void ui_event_onSnookerSave(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        char* output;
        long handicap;

        handicap = strtoul(lv_textarea_get_text(ui_STextAreaHandicap1), &output, 10);
        gui_snooker_setHandicapP1(handicap);

        handicap = strtoul(lv_textarea_get_text(ui_STextAreaHandicap2), &output, 10);
        gui_snooker_setHandicapP2(handicap);

        gui_snooker_set6Red(LV_STATE_CHECKED == lv_obj_get_state(ui_SSwitch6Red));
    }
}

static void ui_event_ScreenSettings(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        ui_refresh_DateTime();
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
        ui_refresh_DateTime();

        lv_label_set_text(ui_SLabelNamePly1, "Игрок 1");
        lv_label_set_text(ui_SLabelNamePly2, "Игрок 2");
        lv_label_set_text(ui_SLabelNamePly3, "Игрок 3");

        lv_obj_clear_state(ui_SSwitch6Red, LV_STATE_CHECKED);
        lv_textarea_set_text(ui_STextAreaHandicap1, "0");
        lv_textarea_set_text(ui_STextAreaHandicap2, "0");
    }
}

static void ui_event_onPlayersSave(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        // copy names to pool and snooker screens
        const char* plyName;
        lv_obj_t* plyLabel;

        plyName = lv_label_get_text(ui_SLabelNamePly1);
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        lv_label_set_text(ui_NPlyLabelName1, plyName);

        plyName = lv_label_get_text(ui_SLabelNamePly2);
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        lv_label_set_text(ui_NPlyLabelName2, plyName);

        plyName = lv_label_get_text(ui_SLabelNamePly3);
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
    }
}

static void ui_event_onSwitchAP(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);

    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        stopConfigPortal();
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        startConfigPortal();
    }
}

static void ui_event_onSwitchDiagnostic(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);

    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        stopDiagnostic();
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        startDiagnostic();
    }
}

static void ui_event_onLabelEdit(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* lb = static_cast<lv_obj_t*>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_comp_set_child(ui_SNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMELABEL, lb);

        lv_textarea_set_text(ui_comp_get_child(ui_SNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), lv_label_get_text(lb));

        _ui_flag_modify(ui_SNameKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_onGreetingSave(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* lb = static_cast<lv_obj_t*>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
        const char* greetingMsg = lv_label_get_text(lb);

        lv_label_set_text(ui_MLabelLogo, greetingMsg);
        saveEEPROMGreeting(greetingMsg);
    }
}

///////////////////// SCREENS ////////////////////
void ui_ScreenSettings_screen_init(void)
{
    ui_ScreenSettings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSettings, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenSettings, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenSettings, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelSettings = lv_obj_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SPanelSettings, lv_pct(90));
    lv_obj_set_height(ui_SPanelSettings, lv_pct(70));
    lv_obj_set_x(ui_SPanelSettings, 0);
    lv_obj_set_y(ui_SPanelSettings, 30);
    lv_obj_set_align(ui_SPanelSettings, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_SPanelSettings, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SPanelSettings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_color(ui_SPanelSettings, lv_color_hex(0x105008), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SPanelSettings, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelConnect = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelConnect, 200);
    lv_obj_set_width(ui_SPanelConnect, lv_pct(100));
    lv_obj_set_align(ui_SPanelConnect, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelConnect, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SPanelConnect, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelConnect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelConnect, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelConnect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelConnect = lv_label_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SLabelConnect, lv_pct(100));
    lv_obj_set_height(ui_SLabelConnect, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelConnect, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelConnect, "Сеть:");
    lv_obj_set_style_text_align(ui_SLabelConnect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelTelega = lv_label_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SLabelTelega, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelTelega, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelTelega, 0);
    lv_obj_set_y(ui_SLabelTelega, 40);
    lv_label_set_text(ui_SLabelTelega, "Отправлять телеграммы");

    ui_SSwitchTelega = lv_switch_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SSwitchTelega, 50);
    lv_obj_set_height(ui_SSwitchTelega, 25);
    lv_obj_set_x(ui_SSwitchTelega, 0);
    lv_obj_set_y(ui_SSwitchTelega, 45);
    lv_obj_set_align(ui_SSwitchTelega, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_state(ui_SSwitchTelega, LV_STATE_CHECKED);     /// States

    lv_obj_set_style_bg_color(ui_SSwitchTelega, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchTelega, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelAP = lv_label_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SLabelAP, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelAP, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelAP, 0);
    lv_obj_set_y(ui_SLabelAP, 90);
    lv_label_set_text(ui_SLabelAP, "Включить точку доступа");

    ui_SSwitchAP = lv_switch_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SSwitchAP, 50);
    lv_obj_set_height(ui_SSwitchAP, 25);
    lv_obj_set_x(ui_SSwitchAP, 0);
    lv_obj_set_y(ui_SSwitchAP, 95);
    lv_obj_set_align(ui_SSwitchAP, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchAP, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchAP, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelInsight = lv_label_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SLabelInsight, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelInsight, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelInsight, 0);
    lv_obj_set_y(ui_SLabelInsight, 140);
    lv_label_set_text(ui_SLabelInsight, "Диагностика Insights");

    ui_SSwitchInsight = lv_switch_create(ui_SPanelConnect);
    lv_obj_set_width(ui_SSwitchInsight, 50);
    lv_obj_set_height(ui_SSwitchInsight, 25);
    lv_obj_set_x(ui_SSwitchInsight, 0);
    lv_obj_set_y(ui_SSwitchInsight, 145);
    lv_obj_set_align(ui_SSwitchInsight, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchInsight, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchInsight, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SPanelPoolPlayers = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_width(ui_SPanelPoolPlayers, lv_pct(100));
    lv_obj_set_height(ui_SPanelPoolPlayers, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_align(ui_SPanelPoolPlayers, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_SPanelPoolPlayers, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SPanelPoolPlayers, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_SPanelPoolPlayers, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SPanelPoolPlayers, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelPoolPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelPoolPlayers, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelPoolPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelPlayers = lv_label_create(ui_SPanelPoolPlayers);
    lv_obj_set_width(ui_SLabelPlayers, lv_pct(100));
    lv_obj_set_height(ui_SLabelPlayers, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelPlayers, -149);
    lv_obj_set_y(ui_SLabelPlayers, -9);
    lv_obj_set_align(ui_SLabelPlayers, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelPlayers, "Игроки:");
    lv_obj_set_style_text_align(ui_SLabelPlayers, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelPly1 = lv_obj_create(ui_SPanelPoolPlayers);
    lv_obj_set_width(ui_SPanelPly1, lv_pct(100));
    lv_obj_set_height(ui_SPanelPly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SPanelPly1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly1 = lv_label_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SLabelNumberPly1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelNumberPly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelNumberPly1, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly1, "1:");

    ui_SLabelNamePly1 = lv_label_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SLabelNamePly1, 225);
    lv_obj_set_height(ui_SLabelNamePly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelNamePly1, -20);
    lv_obj_set_y(ui_SLabelNamePly1, 0);
    lv_obj_set_align(ui_SLabelNamePly1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly1, "Игрок 1");

    ui_SButtonEditPly1 = lv_btn_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SButtonEditPly1, 50);
    lv_obj_set_height(ui_SButtonEditPly1, 50);
    lv_obj_set_align(ui_SButtonEditPly1, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly1, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly1 = lv_label_create(ui_SButtonEditPly1);
    lv_obj_set_width(ui_SLabelEditPly1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelEditPly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelEditPly1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly1, LV_SYMBOL_EDIT);

    ui_SPanelPly2 = lv_obj_create(ui_SPanelPoolPlayers);
    lv_obj_set_width(ui_SPanelPly2, lv_pct(100));
    lv_obj_set_height(ui_SPanelPly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SPanelPly2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly2 = lv_label_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SLabelNumberPly2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelNumberPly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelNumberPly2, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly2, "2:");

    ui_SLabelNamePly2 = lv_label_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SLabelNamePly2, 225);
    lv_obj_set_height(ui_SLabelNamePly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelNamePly2, -20);
    lv_obj_set_y(ui_SLabelNamePly2, 0);
    lv_obj_set_align(ui_SLabelNamePly2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly2, "Игрок 2");

    ui_SButtonEditPly2 = lv_btn_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SButtonEditPly2, 50);
    lv_obj_set_height(ui_SButtonEditPly2, 50);
    lv_obj_set_align(ui_SButtonEditPly2, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly2, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly2 = lv_label_create(ui_SButtonEditPly2);
    lv_obj_set_width(ui_SLabelEditPly2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelEditPly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelEditPly2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly2, LV_SYMBOL_EDIT);

    ui_SPanelPly3 = lv_obj_create(ui_SPanelPoolPlayers);
    lv_obj_set_width(ui_SPanelPly3, lv_pct(100));
    lv_obj_set_height(ui_SPanelPly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SPanelPly3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly3 = lv_label_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SLabelNumberPly3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelNumberPly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelNumberPly3, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly3, "3:");

    ui_SLabelNamePly3 = lv_label_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SLabelNamePly3, 225);
    lv_obj_set_height(ui_SLabelNamePly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelNamePly3, -20);
    lv_obj_set_y(ui_SLabelNamePly3, 0);
    lv_obj_set_align(ui_SLabelNamePly3, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly3, "Игрок 3");

    ui_SButtonEditPly3 = lv_btn_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SButtonEditPly3, 50);
    lv_obj_set_height(ui_SButtonEditPly3, 50);
    lv_obj_set_align(ui_SButtonEditPly3, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly3, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly3 = lv_label_create(ui_SButtonEditPly3);
    lv_obj_set_width(ui_SLabelEditPly3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelEditPly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelEditPly3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly3, LV_SYMBOL_EDIT);

    ui_SButtonPlayerSave = lv_btn_create(ui_SPanelPoolPlayers);
    lv_obj_set_width(ui_SButtonPlayerSave, lv_pct(100));
    lv_obj_set_height(ui_SButtonPlayerSave, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_x(ui_SButtonPlayerSave, 466);
    lv_obj_set_y(ui_SButtonPlayerSave, -10);
    lv_obj_set_align(ui_SButtonPlayerSave, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_SButtonPlayerSave, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonPlayerSave, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonPlayerSave, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonPlayerSave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelPlayerSave = lv_label_create(ui_SButtonPlayerSave);
    lv_obj_set_width(ui_SLabelPlayerSave, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelPlayerSave, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelPlayerSave, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelPlayerSave, LV_SYMBOL_SAVE " Сохранить");

    ui_SPanelSnooker = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelSnooker, 290);
    lv_obj_set_width(ui_SPanelSnooker, lv_pct(100));
    lv_obj_set_x(ui_SPanelSnooker, 15);
    lv_obj_set_y(ui_SPanelSnooker, 65);
    lv_obj_set_align(ui_SPanelSnooker, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_SPanelSnooker, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SPanelSnooker, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelSnooker, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSnooker = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelSnooker, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelSnooker, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelSnooker, "Снукер:");

    ui_SLabel6Red = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabel6Red, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabel6Red, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabel6Red, 0);
    lv_obj_set_y(ui_SLabel6Red, 35);
    lv_label_set_text(ui_SLabel6Red, "6 красных");

    ui_SSwitch6Red = lv_switch_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SSwitch6Red, 50);
    lv_obj_set_height(ui_SSwitch6Red, 25);
    lv_obj_set_x(ui_SSwitch6Red, 0);
    lv_obj_set_y(ui_SSwitch6Red, 35);
    lv_obj_set_align(ui_SSwitch6Red, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitch6Red, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitch6Red, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelHandicap1 = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelHandicap1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelHandicap1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelHandicap1, 0);
    lv_obj_set_y(ui_SLabelHandicap1, 90);
    lv_label_set_text(ui_SLabelHandicap1, "Фора(левый)");

    ui_STextAreaHandicap1 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap1, 100);
    lv_obj_set_height(ui_STextAreaHandicap1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_STextAreaHandicap1, 0);
    lv_obj_set_y(ui_STextAreaHandicap1, 70);
    lv_obj_set_align(ui_STextAreaHandicap1, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap1, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap1, 3);
    lv_textarea_set_text(ui_STextAreaHandicap1, "0");
    lv_textarea_set_one_line(ui_STextAreaHandicap1, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelHandicap2 = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelHandicap2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelHandicap2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelHandicap2, 0);
    lv_obj_set_y(ui_SLabelHandicap2, 150);
    lv_label_set_text(ui_SLabelHandicap2, "Фора(правый)");

    ui_STextAreaHandicap2 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap2, 100);
    lv_obj_set_height(ui_STextAreaHandicap2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_STextAreaHandicap2, 0);
    lv_obj_set_y(ui_STextAreaHandicap2, 130);
    lv_obj_set_align(ui_STextAreaHandicap2, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap2, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap2, 3);
    lv_textarea_set_text(ui_STextAreaHandicap2, "0");
    lv_textarea_set_one_line(ui_STextAreaHandicap2, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SButtonSnookerSave = lv_btn_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SButtonSnookerSave, lv_pct(100));
    lv_obj_set_height(ui_SButtonSnookerSave, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_align(ui_SButtonSnookerSave, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_SButtonSnookerSave, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonSnookerSave, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonSnookerSave, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonSnookerSave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSnookerSave = lv_label_create(ui_SButtonSnookerSave);
    lv_obj_set_width(ui_SLabelSnookerSave, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelSnookerSave, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelSnookerSave, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelSnookerSave, LV_SYMBOL_SAVE " Сохранить");

    ui_SPanelDateTime = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelDateTime, 251);
    lv_obj_set_width(ui_SPanelDateTime, lv_pct(100));
    lv_obj_set_x(ui_SPanelDateTime, 15);
    lv_obj_set_y(ui_SPanelDateTime, 65);
    lv_obj_set_align(ui_SPanelDateTime, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_SPanelDateTime, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SPanelDateTime, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelDateTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelDateTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelDateTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelDate = lv_label_create(ui_SPanelDateTime);
    lv_obj_set_width(ui_SLabelDate, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelDate, 0);
    lv_obj_set_y(ui_SLabelDate, 10);
    lv_label_set_text(ui_SLabelDate, "Дата:");

    ui_STextAreaDate = lv_textarea_create(ui_SPanelDateTime);
    lv_obj_set_width(ui_STextAreaDate, 260);
    lv_obj_set_height(ui_STextAreaDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_STextAreaDate, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_one_line(ui_STextAreaDate, true);

    ui_SLabelTime = lv_label_create(ui_SPanelDateTime);
    lv_obj_set_width(ui_SLabelTime, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelTime, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelTime, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelTime, "Время:");

    ui_SRollerHours = lv_roller_create(ui_SPanelDateTime);
    lv_roller_set_options(ui_SRollerHours, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23", LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_SRollerHours, 90);
    lv_obj_set_width(ui_SRollerHours, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(ui_SRollerHours, 45);
    lv_obj_set_y(ui_SRollerHours, 0);
    lv_obj_set_align(ui_SRollerHours, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_SRollerHours, lv_color_hex(0x105908), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SRollerHours, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_SLabelTimeDots = lv_label_create(ui_SPanelDateTime);
    lv_obj_set_width(ui_SLabelTimeDots, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelTimeDots, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelTimeDots, 95);
    lv_obj_set_y(ui_SLabelTimeDots, 0);
    lv_obj_set_align(ui_SLabelTimeDots, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelTimeDots, ":");

    ui_SRollerMinutes = lv_roller_create(ui_SPanelDateTime);
    lv_roller_set_options(ui_SRollerMinutes, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_SRollerMinutes, 90);
    lv_obj_set_width(ui_SRollerMinutes, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_x(ui_SRollerMinutes, 145);
    lv_obj_set_y(ui_SRollerMinutes, 0);
    lv_obj_set_align(ui_SRollerMinutes, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_SRollerMinutes, lv_color_hex(0x105908), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SRollerMinutes, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_SButtonTimeSave = lv_btn_create(ui_SPanelDateTime);
    lv_obj_set_width(ui_SButtonTimeSave, lv_pct(100));
    lv_obj_set_height(ui_SButtonTimeSave, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_align(ui_SButtonTimeSave, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_SButtonTimeSave, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonTimeSave, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonTimeSave, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonTimeSave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelTimeSave = lv_label_create(ui_SButtonTimeSave);
    lv_obj_set_width(ui_SLabelTimeSave, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelTimeSave, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelTimeSave, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelTimeSave, LV_SYMBOL_SAVE " Сохранить");

    ui_SPanelWelcome = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelWelcome, 200);
    lv_obj_set_width(ui_SPanelWelcome, lv_pct(100));
    lv_obj_set_align(ui_SPanelWelcome, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelWelcome, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SPanelWelcome, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelWelcome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelWelcome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelWelcome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelWelcome = lv_label_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SLabelWelcome, lv_pct(100));
    lv_obj_set_height(ui_SLabelWelcome, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelWelcome, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelWelcome, "Приветствие:");
    lv_obj_set_style_text_align(ui_SLabelWelcome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelGreeting = lv_label_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SLabelGreeting, 285);
    lv_obj_set_height(ui_SLabelGreeting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelGreeting, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SLabelGreeting, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelGreeting, "");
    lv_obj_set_style_text_align(ui_SLabelGreeting, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SButtonEditGreeting = lv_btn_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SButtonEditGreeting, 50);
    lv_obj_set_height(ui_SButtonEditGreeting, 50);
    lv_obj_set_align(ui_SButtonEditGreeting, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditGreeting, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonEditGreeting, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditGreeting, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditGreeting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditGreeting = lv_label_create(ui_SButtonEditGreeting);
    lv_obj_set_width(ui_SLabelEditGreeting, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelEditGreeting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelEditGreeting, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditGreeting, LV_SYMBOL_EDIT);

    ui_SButtonSaveGreeting = lv_btn_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SButtonSaveGreeting, lv_pct(100));
    lv_obj_set_height(ui_SButtonSaveGreeting, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_align(ui_SButtonSaveGreeting, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_SButtonSaveGreeting, LV_OBJ_FLAG_SCROLL_ON_FOCUS);   /// Flags
    lv_obj_clear_flag(ui_SButtonSaveGreeting, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_SButtonSaveGreeting, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonSaveGreeting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSaveGreeting = lv_label_create(ui_SButtonSaveGreeting);
    lv_obj_set_width(ui_SLabelSaveGreeting, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelSaveGreeting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_SLabelSaveGreeting, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelSaveGreeting, LV_SYMBOL_SAVE " Сохранить");

    ui_SLabelHome = lv_label_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SLabelHome, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SLabelHome, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelHome, -200);
    lv_obj_set_y(ui_SLabelHome, 115);
    lv_obj_set_align(ui_SLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_SLabelHome, LV_OBJ_FLAG_CLICKABLE);   /// Flags
    lv_obj_set_style_text_color(ui_SLabelHome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SLabelHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelRefresh = lv_label_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SLabelRefresh, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(ui_SLabelRefresh, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_SLabelRefresh, 200);
    lv_obj_set_y(ui_SLabelRefresh, 115);
    lv_obj_set_align(ui_SLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelRefresh, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_SLabelRefresh, LV_OBJ_FLAG_CLICKABLE);   /// Flags
    lv_obj_set_style_text_color(ui_SLabelRefresh, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SLabelRefresh, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SNameKeyboard = ui_NameKeyboard_create(ui_ScreenSettings);
    lv_obj_set_x(ui_SNameKeyboard, 0);
    lv_obj_set_y(ui_SNameKeyboard, 0);
    lv_obj_add_flag(ui_SNameKeyboard, LV_OBJ_FLAG_HIDDEN);   /// Flags
}

void gui_settings_init()
{
    ui_ScreenSettings_screen_init();

    lv_obj_add_event_cb(ui_ScreenSettings, ui_event_ScreenSettings, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SLabelRefresh, ui_event_onLabelRefresh, LV_EVENT_ALL, NULL);

    // Change date and time
    lv_obj_add_event_cb(ui_STextAreaDate, ui_event_onDateChange, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SButtonTimeSave, ui_event_onDateTimeSave, LV_EVENT_ALL, NULL);

    // Edit player names
    lv_obj_add_event_cb(ui_SButtonEditPly1, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly1);
    lv_obj_add_event_cb(ui_SButtonEditPly2, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly2);
    lv_obj_add_event_cb(ui_SButtonEditPly3, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly3);

    // Save player names
    lv_obj_add_event_cb(ui_SButtonPlayerSave, ui_event_onPlayersSave, LV_EVENT_ALL, NULL);

    // Create default keyboard
    lv_obj_t* ui_SKeyboard = lv_keyboard_create(ui_ScreenSettings);
    lv_keyboard_set_mode(ui_SKeyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_add_flag(ui_SKeyboard, LV_OBJ_FLAG_HIDDEN);
    
    // Snooker
    lv_obj_add_event_cb(ui_STextAreaHandicap1, ui_event_onHandicapUpdate, LV_EVENT_ALL, ui_SKeyboard);
    lv_obj_add_event_cb(ui_STextAreaHandicap2, ui_event_onHandicapUpdate, LV_EVENT_ALL, ui_SKeyboard);
    lv_obj_add_event_cb(ui_SButtonSnookerSave, ui_event_onSnookerSave, LV_EVENT_ALL, NULL);

    // start/stop AP
    lv_obj_add_event_cb(ui_SSwitchAP, ui_event_onSwitchAP, LV_EVENT_ALL, NULL);

    // start/stop Diagnostics
    lv_obj_add_event_cb(ui_SSwitchInsight, ui_event_onSwitchDiagnostic, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_SButtonEditGreeting, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelGreeting);
    lv_obj_add_event_cb(ui_SButtonSaveGreeting, ui_event_onGreetingSave, LV_EVENT_ALL, ui_SLabelGreeting);

}
