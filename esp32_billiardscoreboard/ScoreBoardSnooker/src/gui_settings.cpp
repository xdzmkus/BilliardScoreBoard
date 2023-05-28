#include "gui_settings.h"
#include "gui_components.h"
#include "gui_main.h"
#include "gui_pool.h"
#include "gui_snooker.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenSettings;
lv_obj_t* ui_SLabelHome;
lv_obj_t* ui_SLabelRefresh;
lv_obj_t* ui_SPanelSettings;
lv_obj_t* ui_SPanelPlayers;
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
lv_obj_t* ui_SPanelSnooker;
lv_obj_t* ui_SLabelSnooker;
lv_obj_t* ui_SLabel6Red;
lv_obj_t* ui_SSwitch6Red;
lv_obj_t* ui_SLabelHandicap1;
lv_obj_t* ui_STextAreaHandicap1;
lv_obj_t* ui_SLabelHandicap2;
lv_obj_t* ui_STextAreaHandicap2;
lv_obj_t* ui_SPanelWelcome;
lv_obj_t* ui_SLabelWelcome;
lv_obj_t* ui_SLabelGreeting;
lv_obj_t* ui_SButtonEditGreeting;
lv_obj_t* ui_SLabelEditGreeting;
lv_obj_t* ui_SButtonSaveGreeting;
lv_obj_t* ui_SLabelSaveGreeting;

lv_obj_t* ui_SNameKeyboard;
lv_obj_t* ui_SKeyboard;

extern const char* getGreetingMsg();
extern void saveEEPROMGreeting(const char* msg);

///////////////////// FUNCTIONS ////////////////////

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
        lv_label_set_text(ui_SLabelNamePly1, "");
        lv_event_send(ui_SLabelNamePly1, LV_EVENT_VALUE_CHANGED, NULL);

        lv_label_set_text(ui_SLabelNamePly2, "");
        lv_event_send(ui_SLabelNamePly2, LV_EVENT_VALUE_CHANGED, NULL);

        lv_label_set_text(ui_SLabelNamePly3, "");
        lv_event_send(ui_SLabelNamePly3, LV_EVENT_VALUE_CHANGED, NULL);

        lv_obj_clear_state(ui_SSwitch6Red, LV_STATE_CHECKED);
        gui_snooker_set6Red(false);

        lv_textarea_set_text(ui_STextAreaHandicap1, "0");
        gui_snooker_setHandicapP1(0);

        lv_textarea_set_text(ui_STextAreaHandicap2, "0");
        gui_snooker_setHandicapP2(0);
    }
}

static void ui_event_onPlayer1Changed(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
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
    }
}

static void ui_event_onPlayer2Changed(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        // copy names to pool and snooker screens
        const char* plyName;
        lv_obj_t* plyLabel;

        plyName = lv_label_get_text(ui_SLabelNamePly2);
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
        lv_label_set_text(ui_NPlyLabelName2, plyName);
    }
}

static void ui_event_onPlayer3Changed(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        // copy names to pool and snooker screens
        const char* plyName;
        lv_obj_t* plyLabel;

        plyName = lv_label_get_text(ui_SLabelNamePly3);
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, plyName);
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

static void ui_event_on6RedUpdate(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        gui_snooker_set6Red(lv_obj_has_state(target, LV_STATE_CHECKED));
    }
}

static void ui_event_onHandicapUpdate(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);

    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(ui_SKeyboard, ta);
        lv_obj_set_style_max_height(ui_SKeyboard, LV_HOR_RES * 2 / 3, 0);
        lv_obj_update_layout(ui_SPanelSettings);   /*Be sure the sizes are recalculated*/
        lv_obj_set_height(ui_SPanelSettings, lv_pct(50));
        lv_obj_clear_flag(ui_SKeyboard, LV_OBJ_FLAG_HIDDEN);
        lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
    }
    else if (code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(ui_SKeyboard, NULL);
        lv_obj_set_height(ui_SPanelSettings, lv_pct(70));
        lv_obj_add_flag(ui_SKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
    else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_set_height(ui_SPanelSettings, lv_pct(70));
        lv_obj_add_flag(ui_SKeyboard, LV_OBJ_FLAG_HIDDEN);

        char* output;
        long handicap;

        if (ta == ui_STextAreaHandicap1)
        {
            handicap = strtoul(lv_textarea_get_text(ui_STextAreaHandicap1), &output, 10);
            gui_snooker_setHandicapP1(handicap);
        }
        else if (ta == ui_STextAreaHandicap2)
        {
            handicap = strtoul(lv_textarea_get_text(ui_STextAreaHandicap2), &output, 10);
            gui_snooker_setHandicapP2(handicap);
        }
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

static void ui_event_ScreenSettings(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        lv_obj_scroll_to_y(ui_SPanelSettings, 0, LV_ANIM_ON);

        // Create name's keyboard
        ui_SNameKeyboard = ui_NameKeyboard_create(ui_ScreenSettings);
        lv_obj_set_x(ui_SNameKeyboard, 0);
        lv_obj_set_y(ui_SNameKeyboard, 0);
        lv_obj_add_flag(ui_SNameKeyboard, LV_OBJ_FLAG_HIDDEN);

        // Create numeric keyboard
        ui_SKeyboard = lv_keyboard_create(ui_ScreenSettings);
        lv_keyboard_set_mode(ui_SKeyboard, LV_KEYBOARD_MODE_NUMBER);
        lv_obj_add_flag(ui_SKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
    if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        lv_obj_del(ui_SNameKeyboard);
        lv_obj_del(ui_SKeyboard);
    }
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenSettings_screen_init(void)
{
    ui_ScreenSettings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenSettings, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenSettings, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelHome = lv_label_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SLabelHome, 60);
    lv_obj_set_height(ui_SLabelHome, 50);
    lv_obj_set_x(ui_SLabelHome, -200);
    lv_obj_set_y(ui_SLabelHome, 125);
    lv_obj_set_align(ui_SLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_SLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_SLabelHome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SLabelHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_SLabelHome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelRefresh = lv_label_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SLabelRefresh, 60);
    lv_obj_set_height(ui_SLabelRefresh, 50);
    lv_obj_set_x(ui_SLabelRefresh, 200);
    lv_obj_set_y(ui_SLabelRefresh, 125);
    lv_obj_set_align(ui_SLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelRefresh, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_SLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_SLabelRefresh, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SLabelRefresh, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_SLabelRefresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

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

    ui_SPanelPlayers = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_width(ui_SPanelPlayers, lv_pct(100));
    lv_obj_set_height(ui_SPanelPlayers, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelPlayers, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_SPanelPlayers, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SPanelPlayers, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_SPanelPlayers, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelPlayers, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelPlayers, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelPlayers, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelPlayers = lv_label_create(ui_SPanelPlayers);
    lv_obj_set_width(ui_SLabelPlayers, lv_pct(100));
    lv_obj_set_height(ui_SLabelPlayers, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelPlayers, -149);
    lv_obj_set_y(ui_SLabelPlayers, -36);
    lv_obj_set_align(ui_SLabelPlayers, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelPlayers, "Игроки:");
    lv_obj_set_style_text_align(ui_SLabelPlayers, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelPly1 = lv_obj_create(ui_SPanelPlayers);
    lv_obj_set_height(ui_SPanelPly1, 60);
    lv_obj_set_width(ui_SPanelPly1, lv_pct(100));
    lv_obj_set_align(ui_SPanelPly1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly1 = lv_label_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SLabelNumberPly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelNumberPly1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelNumberPly1, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly1, "1:");

    ui_SLabelNamePly1 = lv_label_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SLabelNamePly1, 225);
    lv_obj_set_height(ui_SLabelNamePly1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelNamePly1, -20);
    lv_obj_set_y(ui_SLabelNamePly1, 0);
    lv_obj_set_align(ui_SLabelNamePly1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly1, "Игрок 1");

    ui_SButtonEditPly1 = lv_btn_create(ui_SPanelPly1);
    lv_obj_set_width(ui_SButtonEditPly1, 50);
    lv_obj_set_height(ui_SButtonEditPly1, 50);
    lv_obj_set_align(ui_SButtonEditPly1, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly1, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly1 = lv_label_create(ui_SButtonEditPly1);
    lv_obj_set_width(ui_SLabelEditPly1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditPly1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditPly1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly1, LV_SYMBOL_EDIT);

    ui_SPanelPly2 = lv_obj_create(ui_SPanelPlayers);
    lv_obj_set_height(ui_SPanelPly2, 60);
    lv_obj_set_width(ui_SPanelPly2, lv_pct(100));
    lv_obj_set_align(ui_SPanelPly2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly2 = lv_label_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SLabelNumberPly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelNumberPly2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelNumberPly2, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly2, "2:");

    ui_SLabelNamePly2 = lv_label_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SLabelNamePly2, 225);
    lv_obj_set_height(ui_SLabelNamePly2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelNamePly2, -20);
    lv_obj_set_y(ui_SLabelNamePly2, 0);
    lv_obj_set_align(ui_SLabelNamePly2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly2, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly2, "Игрок 2");

    ui_SButtonEditPly2 = lv_btn_create(ui_SPanelPly2);
    lv_obj_set_width(ui_SButtonEditPly2, 50);
    lv_obj_set_height(ui_SButtonEditPly2, 50);
    lv_obj_set_align(ui_SButtonEditPly2, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly2, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly2 = lv_label_create(ui_SButtonEditPly2);
    lv_obj_set_width(ui_SLabelEditPly2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditPly2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditPly2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly2, LV_SYMBOL_EDIT);

    ui_SPanelPly3 = lv_obj_create(ui_SPanelPlayers);
    lv_obj_set_height(ui_SPanelPly3, 60);
    lv_obj_set_width(ui_SPanelPly3, lv_pct(100));
    lv_obj_set_align(ui_SPanelPly3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelPly3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_side(ui_SPanelPly3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelNumberPly3 = lv_label_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SLabelNumberPly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelNumberPly3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelNumberPly3, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SLabelNumberPly3, "3:");

    ui_SLabelNamePly3 = lv_label_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SLabelNamePly3, 225);
    lv_obj_set_height(ui_SLabelNamePly3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelNamePly3, -20);
    lv_obj_set_y(ui_SLabelNamePly3, 0);
    lv_obj_set_align(ui_SLabelNamePly3, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_SLabelNamePly3, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelNamePly3, "Игрок 3");

    ui_SButtonEditPly3 = lv_btn_create(ui_SPanelPly3);
    lv_obj_set_width(ui_SButtonEditPly3, 50);
    lv_obj_set_height(ui_SButtonEditPly3, 50);
    lv_obj_set_align(ui_SButtonEditPly3, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditPly3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditPly3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditPly3, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditPly3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditPly3 = lv_label_create(ui_SButtonEditPly3);
    lv_obj_set_width(ui_SLabelEditPly3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditPly3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditPly3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditPly3, LV_SYMBOL_EDIT);

    ui_SPanelSnooker = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelSnooker, 230);
    lv_obj_set_width(ui_SPanelSnooker, lv_pct(100));
    lv_obj_set_x(ui_SPanelSnooker, 15);
    lv_obj_set_y(ui_SPanelSnooker, 65);
    lv_obj_set_align(ui_SPanelSnooker, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_SPanelSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelSnooker, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelSnooker, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSnooker = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelSnooker, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelSnooker, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelSnooker, "Снукер:");

    ui_SLabel6Red = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabel6Red, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabel6Red, LV_SIZE_CONTENT);    /// 1
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
    lv_obj_set_width(ui_SLabelHandicap1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelHandicap1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelHandicap1, 0);
    lv_obj_set_y(ui_SLabelHandicap1, 90);
    lv_label_set_text(ui_SLabelHandicap1, "Фора 1:");

    ui_STextAreaHandicap1 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap1, 90);
    lv_obj_set_height(ui_STextAreaHandicap1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_STextAreaHandicap1, 0);
    lv_obj_set_y(ui_STextAreaHandicap1, 80);
    lv_obj_set_align(ui_STextAreaHandicap1, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap1, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap1, 3);
    lv_textarea_set_text(ui_STextAreaHandicap1, "0");
    lv_textarea_set_one_line(ui_STextAreaHandicap1, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelHandicap2 = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelHandicap2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelHandicap2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelHandicap2, 0);
    lv_obj_set_y(ui_SLabelHandicap2, 150);
    lv_label_set_text(ui_SLabelHandicap2, "Фора 2:");

    ui_STextAreaHandicap2 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap2, 90);
    lv_obj_set_height(ui_STextAreaHandicap2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_STextAreaHandicap2, 0);
    lv_obj_set_y(ui_STextAreaHandicap2, 140);
    lv_obj_set_align(ui_STextAreaHandicap2, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap2, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap2, 3);
    lv_textarea_set_text(ui_STextAreaHandicap2, "0");
    lv_textarea_set_one_line(ui_STextAreaHandicap2, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelWelcome = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelWelcome, 200);
    lv_obj_set_width(ui_SPanelWelcome, lv_pct(100));
    lv_obj_set_align(ui_SPanelWelcome, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelWelcome, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelWelcome, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelWelcome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelWelcome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelWelcome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelWelcome = lv_label_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SLabelWelcome, lv_pct(100));
    lv_obj_set_height(ui_SLabelWelcome, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelWelcome, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelWelcome, "Приветствие:");
    lv_obj_set_style_text_align(ui_SLabelWelcome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelGreeting = lv_label_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SLabelGreeting, 285);
    lv_obj_set_height(ui_SLabelGreeting, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelGreeting, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_SLabelGreeting, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_SLabelGreeting, "");
    lv_obj_set_style_text_align(ui_SLabelGreeting, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SButtonEditGreeting = lv_btn_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SButtonEditGreeting, 50);
    lv_obj_set_height(ui_SButtonEditGreeting, 50);
    lv_obj_set_align(ui_SButtonEditGreeting, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditGreeting, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditGreeting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditGreeting, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditGreeting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditGreeting = lv_label_create(ui_SButtonEditGreeting);
    lv_obj_set_width(ui_SLabelEditGreeting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditGreeting, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditGreeting, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditGreeting, LV_SYMBOL_EDIT);

    ui_SButtonSaveGreeting = lv_btn_create(ui_SPanelWelcome);
    lv_obj_set_width(ui_SButtonSaveGreeting, lv_pct(100));
    lv_obj_set_height(ui_SButtonSaveGreeting, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SButtonSaveGreeting, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_SButtonSaveGreeting, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonSaveGreeting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonSaveGreeting, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonSaveGreeting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSaveGreeting = lv_label_create(ui_SButtonSaveGreeting);
    lv_obj_set_width(ui_SLabelSaveGreeting, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelSaveGreeting, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelSaveGreeting, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelSaveGreeting, LV_SYMBOL_SAVE " Сохранить");

}

///////////////////// EXPORT ////////////////////

void gui_settings_init()
{
    ui_ScreenSettings_screen_init();

    lv_label_set_text(ui_SLabelGreeting, getGreetingMsg());

    // Load/Unload screen
    lv_obj_add_event_cb(ui_ScreenSettings, ui_event_ScreenSettings, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_SLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SLabelRefresh, ui_event_onLabelRefresh, LV_EVENT_ALL, NULL);

    // Edit player names
    lv_obj_add_event_cb(ui_SButtonEditPly1, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly1);
    lv_obj_add_event_cb(ui_SButtonEditPly2, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly2);
    lv_obj_add_event_cb(ui_SButtonEditPly3, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelNamePly3);

    // Save player names
    lv_obj_add_event_cb(ui_SLabelNamePly1, ui_event_onPlayer1Changed, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SLabelNamePly2, ui_event_onPlayer2Changed, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SLabelNamePly3, ui_event_onPlayer3Changed, LV_EVENT_ALL, NULL);

    // Snooker
    lv_obj_add_event_cb(ui_SSwitch6Red, ui_event_on6RedUpdate, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_STextAreaHandicap1, ui_event_onHandicapUpdate, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_STextAreaHandicap2, ui_event_onHandicapUpdate, LV_EVENT_ALL, NULL);

    // Edit greeting message
    lv_obj_add_event_cb(ui_SButtonEditGreeting, ui_event_onLabelEdit, LV_EVENT_ALL, ui_SLabelGreeting);
    lv_obj_add_event_cb(ui_SButtonSaveGreeting, ui_event_onGreetingSave, LV_EVENT_ALL, ui_SLabelGreeting);

}
