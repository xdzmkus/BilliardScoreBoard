#include "gui_settings.h"
#include "gui_main.h"
#include "gui.h"
#include "defs.h"
#include "EEPROMHelper.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_ScreenSettings
lv_obj_t * ui_ScreenSettings;
lv_obj_t * ui_SLabelHome;
lv_obj_t * ui_SPanelSettings;
lv_obj_t * ui_SButtonRestore;
lv_obj_t * ui_SLabelRestore;
lv_obj_t * ui_SPanelGeneral;
lv_obj_t * ui_SLabelWifi;
lv_obj_t * ui_SSwitchWifi;
lv_obj_t * ui_SLabelTelega;
lv_obj_t * ui_SSwitchTelega;
lv_obj_t * ui_SLabelAudio;
lv_obj_t * ui_SSwitchAudio;
lv_obj_t * ui_SLabelVolume;
lv_obj_t * ui_SSliderVolume;
lv_obj_t * ui_SLabelAP;
lv_obj_t * ui_SSwitchAP;
lv_obj_t * ui_SPanelSnooker;
lv_obj_t * ui_SLabelSnooker;
lv_obj_t * ui_SLabel6Red;
lv_obj_t * ui_SSwitch6Red;
lv_obj_t * ui_SLabelControlBalls;
lv_obj_t * ui_SSwitchControlBalls;
lv_obj_t * ui_SLabekHandicap1;
lv_obj_t * ui_STextAreaHandicap1;
lv_obj_t * ui_SButtonEditHandicap1;
lv_obj_t * ui_SLabelEditHandicap1;
lv_obj_t * ui_SLabekHandicap2;
lv_obj_t * ui_STextAreaHandicap2;
lv_obj_t * ui_SButtonEditHandicap2;
lv_obj_t * ui_SLabelEditHandicap2;
lv_obj_t * ui_SPanelOptions;
lv_obj_t * ui_SLabelOptions;
lv_obj_t * ui_SPanelOptions1;
lv_obj_t * ui_STextAreaGreeting;
lv_obj_t * ui_SButtonEditGreeting;
lv_obj_t * ui_SLabelEditGreeting;
lv_obj_t * ui_SPanelOptions2;
lv_obj_t * ui_STextAreaSSID;
lv_obj_t * ui_SButtonEditSSID;
lv_obj_t * ui_SLabelEditSSID;
lv_obj_t * ui_SPanelOptions3;
lv_obj_t * ui_STextAreaWifiPass;
lv_obj_t * ui_SButtonEditWifiPass;
lv_obj_t * ui_SLabelEditWifiPass;
lv_obj_t * ui_SPanelOptions4;
lv_obj_t * ui_STextAreaTelegaChannel;
lv_obj_t * ui_SButtonEditTelegaChannel;
lv_obj_t * ui_SLabelEditTelegaChannel;
lv_obj_t * ui_SPanelOptions5;
lv_obj_t * ui_STextAreaMqttHost;
lv_obj_t * ui_SButtonEditMqttHost;
lv_obj_t * ui_SLabelEditMqttHost;
lv_obj_t * ui_SPanelOptions6;
lv_obj_t * ui_STextAreaMqttPort;
lv_obj_t * ui_SButtonEditMqttPort;
lv_obj_t * ui_SLabelEditMqttPort;
lv_obj_t * ui_SPanelOptions7;
lv_obj_t * ui_STextAreaMqttUser;
lv_obj_t * ui_SButtonEditMqttUser;
lv_obj_t * ui_SLabelEditMqttUser;
lv_obj_t * ui_SPanelOptions8;
lv_obj_t * ui_STextAreaMqttPass;
lv_obj_t * ui_SButtonEditMqttPass;
lv_obj_t * ui_SLabelEditMqttPass;
lv_obj_t * ui_SButtonSaveAll;
lv_obj_t * ui_SLabelSaveAll;
lv_obj_t * ui_SOptionKeyboard;

// SCREEN: ui_ScreenRestore
lv_obj_t* ui_ScreenRestore;
lv_obj_t* ui_RLabelQuestion;
lv_obj_t* ui_RLabelWait;
lv_obj_t* ui_RButtonYes;
lv_obj_t* ui_RLabelYes;
lv_obj_t* ui_RButtonCancel;
lv_obj_t* ui_RLabelCancel;

static lv_timer_t* restoreTimer;

///////////////////// FUNCTIONS ////////////////////

static void ui_hideRestoreScreen(lv_timer_t* timer)
{
    // if state is received then hide screen
    if (!gui_stateAwaiting())
    {
        lv_timer_del(timer);

        _ui_screen_change(&ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_settings_create);
    }
}

///////////////////// EVENTS ////////////////////

static void ui_event_ScreenSettings(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        // set board state
        _ui_state_modify(ui_SSwitchAP, LV_STATE_CHECKED, boardSettings.isAPEnabled ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SSwitchWifi, LV_STATE_CHECKED, boardSettings.isWifiEnabled ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SSwitchTelega, LV_STATE_CHECKED, boardSettings.isTelegaEnabled ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SSwitchAudio, LV_STATE_CHECKED, boardSettings.isAudioEnabled ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        lv_slider_set_value(ui_SSliderVolume, boardSettings.audioVolume, LV_ANIM_OFF);

        // set eeprom data
        lv_textarea_set_text(ui_STextAreaGreeting, boardEEPROMdata.greeting);
        lv_textarea_set_text(ui_STextAreaSSID, boardEEPROMdata.sta_ssid);
        lv_textarea_set_text(ui_STextAreaWifiPass, boardEEPROMdata.sta_pass);
        lv_textarea_set_text(ui_STextAreaTelegaChannel, boardEEPROMdata.bot_channel);
        lv_textarea_set_text(ui_STextAreaMqttHost, boardEEPROMdata.mqtt_host);
        lv_textarea_set_text(ui_STextAreaMqttPort, boardEEPROMdata.mqtt_port);
        lv_textarea_set_text(ui_STextAreaMqttUser, boardEEPROMdata.mqtt_user);
        lv_textarea_set_text(ui_STextAreaMqttPass, boardEEPROMdata.mqtt_pass);

        // set snooker options
        _ui_state_modify(ui_SSwitch6Red, LV_STATE_CHECKED, boardPublishing.snooker6Red ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_SSwitchControlBalls, LV_STATE_CHECKED, boardPublishing.snookerControlBalls ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        
        char handicap[4];
        sprintf(handicap, "%d", boardPublishing.snookerPly1Handicap);
        lv_textarea_set_text(ui_STextAreaHandicap1, handicap);
        sprintf(handicap, "%d", boardPublishing.snookerPly2Handicap);
        lv_textarea_set_text(ui_STextAreaHandicap2, handicap);
    }
    if (event_code == LV_EVENT_SCREEN_UNLOAD_START)
    {
        boardPublishing.snooker6Red = lv_obj_has_state(ui_SSwitch6Red, LV_STATE_CHECKED);
        boardPublishing.snookerControlBalls = lv_obj_has_state(ui_SSwitchControlBalls, LV_STATE_CHECKED);
        boardPublishing.snookerPly1Handicap = atoi(lv_textarea_get_text(ui_STextAreaHandicap1));
        boardPublishing.snookerPly2Handicap = atoi(lv_textarea_get_text(ui_STextAreaHandicap2));
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

static void ui_event_SSwitchAP(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        gui_turnAP(lv_obj_has_state(target, LV_STATE_CHECKED));
    }
}

static void ui_event_SSwitchWifi(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        gui_turnWiFi(lv_obj_has_state(target, LV_STATE_CHECKED));
    }
}

static void ui_event_SSwitchTelega(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        gui_turnTelegram(lv_obj_has_state(target, LV_STATE_CHECKED));
    }
}

static void ui_event_SSwitchAudio(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        gui_turnAudio(lv_obj_has_state(target, LV_STATE_CHECKED));
    }
}

static void ui_event_SSliderVolume(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = static_cast<lv_obj_t*>(lv_event_get_target(e));

    if (event_code == LV_EVENT_RELEASED)
    {
        gui_setVolume(static_cast<uint8_t>(lv_slider_get_value(target)));
    }
}

static void ui_event_onOptionEdit(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* lb = static_cast<lv_obj_t*>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
   		ui_comp_set_child(ui_SOptionKeyboard, UI_COMP_OPTIONSKEYBOARD_EXPORTTEXTAREA, lb);

        // copy settings of textarea
        lv_textarea_set_max_length(ui_comp_get_child(ui_SOptionKeyboard, UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA), lv_textarea_get_max_length(lb));
        lv_textarea_set_password_mode(ui_comp_get_child(ui_SOptionKeyboard, UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA), lv_textarea_get_password_mode(lb));
        lv_textarea_set_text(ui_comp_get_child(ui_SOptionKeyboard, UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA), lv_textarea_get_text(lb));
        lv_textarea_set_placeholder_text(ui_comp_get_child(ui_SOptionKeyboard, UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA), lv_textarea_get_placeholder_text(lb));

        _ui_flag_modify(ui_SOptionKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_onOptionsSave(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        strncpy(boardEEPROMdata.greeting, lv_textarea_get_text(ui_STextAreaGreeting), sizeof(boardEEPROMdata.greeting) - 1);
        strncpy(boardEEPROMdata.sta_ssid, lv_textarea_get_text(ui_STextAreaSSID), sizeof(boardEEPROMdata.sta_ssid) - 1);
        strncpy(boardEEPROMdata.sta_pass, lv_textarea_get_text(ui_STextAreaWifiPass), sizeof(boardEEPROMdata.sta_pass) - 1);
        strncpy(boardEEPROMdata.bot_channel, lv_textarea_get_text(ui_STextAreaTelegaChannel), sizeof(boardEEPROMdata.bot_channel) - 1);
        strncpy(boardEEPROMdata.mqtt_host, lv_textarea_get_text(ui_STextAreaMqttHost), sizeof(boardEEPROMdata.mqtt_host) - 1);
        strncpy(boardEEPROMdata.mqtt_port, lv_textarea_get_text(ui_STextAreaMqttPort), sizeof(boardEEPROMdata.mqtt_port) - 1);
        strncpy(boardEEPROMdata.mqtt_user, lv_textarea_get_text(ui_STextAreaMqttUser), sizeof(boardEEPROMdata.mqtt_user) - 1);
        strncpy(boardEEPROMdata.mqtt_pass, lv_textarea_get_text(ui_STextAreaMqttPass), sizeof(boardEEPROMdata.mqtt_pass) - 1);

        saveEEPROMdata();

        ESP.restart();
    }
}

static void ui_event_SButtonRestore(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        restoreTimer = NULL;

        _ui_screen_change(&ui_ScreenRestore, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_restore_create);
    }
}

static void ui_event_RButtonYes(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_RButtonYes, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        gui_stateRequest();

        restoreTimer = lv_timer_create(ui_hideRestoreScreen, 1000, NULL); // hide screen when restore is done

        lv_timer_set_repeat_count(restoreTimer, -1);
    }
}

static void ui_event_RButtonCancel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        gui_stateRevoke();

        if (restoreTimer != NULL) lv_timer_del(restoreTimer);

        _ui_screen_change(&ui_ScreenSettings, LV_SCR_LOAD_ANIM_NONE, 0, 0, &gui_settings_create);
    }
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenSettings_screen_init(void)
{
    ui_ScreenSettings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_image_src(ui_ScreenSettings, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenSettings, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelHome = lv_label_create(ui_ScreenSettings);
    lv_obj_set_width(ui_SLabelHome, 108);
    lv_obj_set_height(ui_SLabelHome, 50);
    lv_obj_set_x(ui_SLabelHome, -158);
    lv_obj_set_y(ui_SLabelHome, 126);
    lv_obj_set_align(ui_SLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelHome, LV_SYMBOL_HOME " Назад");
    lv_obj_add_flag(ui_SLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_SLabelHome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SLabelHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_SLabelHome, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

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

    ui_SButtonRestore = lv_btn_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SButtonRestore, 50);
    lv_obj_set_width(ui_SButtonRestore, lv_pct(100));
    lv_obj_set_align(ui_SButtonRestore, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonRestore, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonRestore, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonRestore, lv_color_hex(0x0B4105), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonRestore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelRestore = lv_label_create(ui_SButtonRestore);
    lv_obj_set_width(ui_SLabelRestore, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelRestore, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelRestore, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelRestore, "Восстановить счёт");

    ui_SPanelGeneral = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelGeneral, 260);
    lv_obj_set_width(ui_SPanelGeneral, lv_pct(100));
    lv_obj_set_x(ui_SPanelGeneral, 15);
    lv_obj_set_y(ui_SPanelGeneral, 65);
    lv_obj_set_align(ui_SPanelGeneral, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_SPanelGeneral, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelGeneral, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelGeneral, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelGeneral, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelGeneral, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelWifi = lv_label_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SLabelWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelWifi, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_SLabelWifi, "Включить WiFi");

    ui_SSwitchWifi = lv_switch_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SSwitchWifi, 50);
    lv_obj_set_height(ui_SSwitchWifi, 25);
    lv_obj_set_x(ui_SSwitchWifi, 0);
    lv_obj_set_y(ui_SSwitchWifi, 5);
    lv_obj_set_align(ui_SSwitchWifi, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchWifi, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchWifi, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelTelega = lv_label_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SLabelTelega, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelTelega, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelTelega, 0);
    lv_obj_set_y(ui_SLabelTelega, 50);
    lv_label_set_text(ui_SLabelTelega, "Отправлять телеграммы");

    ui_SSwitchTelega = lv_switch_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SSwitchTelega, 50);
    lv_obj_set_height(ui_SSwitchTelega, 25);
    lv_obj_set_x(ui_SSwitchTelega, 0);
    lv_obj_set_y(ui_SSwitchTelega, 55);
    lv_obj_set_align(ui_SSwitchTelega, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchTelega, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchTelega, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelAudio = lv_label_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SLabelAudio, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelAudio, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelAudio, 0);
    lv_obj_set_y(ui_SLabelAudio, 100);
    lv_label_set_text(ui_SLabelAudio, "Голосовое сообщение");

    ui_SSwitchAudio = lv_switch_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SSwitchAudio, 50);
    lv_obj_set_height(ui_SSwitchAudio, 25);
    lv_obj_set_x(ui_SSwitchAudio, 0);
    lv_obj_set_y(ui_SSwitchAudio, 105);
    lv_obj_set_align(ui_SSwitchAudio, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchAudio, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchAudio, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelVolume = lv_label_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SLabelVolume, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelVolume, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelVolume, 0);
    lv_obj_set_y(ui_SLabelVolume, 150);
    lv_label_set_text(ui_SLabelVolume, "Громкость");

    ui_SSliderVolume = lv_slider_create(ui_SPanelGeneral);
    lv_slider_set_range(ui_SSliderVolume, 1, 10);
    lv_slider_set_value(ui_SSliderVolume, 5, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_SSliderVolume) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_SSliderVolume, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_SSliderVolume, 200);
    lv_obj_set_height(ui_SSliderVolume, 15);
    lv_obj_set_x(ui_SSliderVolume, 155);
    lv_obj_set_y(ui_SSliderVolume, 160);


    ui_SLabelAP = lv_label_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SLabelAP, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelAP, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelAP, 0);
    lv_obj_set_y(ui_SLabelAP, 200);
    lv_label_set_text(ui_SLabelAP, "Точка доступа");

    ui_SSwitchAP = lv_switch_create(ui_SPanelGeneral);
    lv_obj_set_width(ui_SSwitchAP, 50);
    lv_obj_set_height(ui_SSwitchAP, 25);
    lv_obj_set_x(ui_SSwitchAP, 0);
    lv_obj_set_y(ui_SSwitchAP, 205);
    lv_obj_set_align(ui_SSwitchAP, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchAP, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchAP, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SPanelSnooker = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_height(ui_SPanelSnooker, 270);
    lv_obj_set_width(ui_SPanelSnooker, lv_pct(100));
    lv_obj_set_x(ui_SPanelSnooker, 15);
    lv_obj_set_y(ui_SPanelSnooker, 66);
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
    lv_label_set_text(ui_SLabelSnooker, "Снукер");

    ui_SLabel6Red = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabel6Red, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabel6Red, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabel6Red, 0);
    lv_obj_set_y(ui_SLabel6Red, 40);
    lv_label_set_text(ui_SLabel6Red, "6 красных");

    ui_SSwitch6Red = lv_switch_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SSwitch6Red, 50);
    lv_obj_set_height(ui_SSwitch6Red, 25);
    lv_obj_set_x(ui_SSwitch6Red, 0);
    lv_obj_set_y(ui_SSwitch6Red, 45);
    lv_obj_set_align(ui_SSwitch6Red, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitch6Red, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitch6Red, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabelControlBalls = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabelControlBalls, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelControlBalls, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabelControlBalls, 0);
    lv_obj_set_y(ui_SLabelControlBalls, 80);
    lv_label_set_text(ui_SLabelControlBalls, "Контроль шаров");

    ui_SSwitchControlBalls = lv_switch_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SSwitchControlBalls, 50);
    lv_obj_set_height(ui_SSwitchControlBalls, 25);
    lv_obj_set_x(ui_SSwitchControlBalls, 0);
    lv_obj_set_y(ui_SSwitchControlBalls, 85);
    lv_obj_set_align(ui_SSwitchControlBalls, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_bg_color(ui_SSwitchControlBalls, lv_color_hex(0x105908), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_SSwitchControlBalls, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_SLabekHandicap1 = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabekHandicap1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabekHandicap1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabekHandicap1, 0);
    lv_obj_set_y(ui_SLabekHandicap1, 130);
    lv_label_set_text(ui_SLabekHandicap1, "Фора игрока 1");

    ui_STextAreaHandicap1 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap1, 107);
    lv_obj_set_height(ui_STextAreaHandicap1, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_STextAreaHandicap1, 65);
    lv_obj_set_y(ui_STextAreaHandicap1, 120);
    lv_obj_set_align(ui_STextAreaHandicap1, LV_ALIGN_TOP_MID);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap1, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap1, 3);
    lv_textarea_set_text(ui_STextAreaHandicap1, "0");
    lv_textarea_set_placeholder_text(ui_STextAreaHandicap1, "Фора...");
    lv_textarea_set_one_line(ui_STextAreaHandicap1, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_SButtonEditHandicap1 = lv_btn_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SButtonEditHandicap1, 50);
    lv_obj_set_height(ui_SButtonEditHandicap1, 50);
    lv_obj_set_x(ui_SButtonEditHandicap1, 0);
    lv_obj_set_y(ui_SButtonEditHandicap1, 120);
    lv_obj_set_align(ui_SButtonEditHandicap1, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_SButtonEditHandicap1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditHandicap1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditHandicap1, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditHandicap1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditHandicap1 = lv_label_create(ui_SButtonEditHandicap1);
    lv_obj_set_width(ui_SLabelEditHandicap1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditHandicap1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditHandicap1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditHandicap1, LV_SYMBOL_EDIT);

    ui_SLabekHandicap2 = lv_label_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SLabekHandicap2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabekHandicap2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLabekHandicap2, 1);
    lv_obj_set_y(ui_SLabekHandicap2, 190);
    lv_label_set_text(ui_SLabekHandicap2, "Фора игрока 2");

    ui_STextAreaHandicap2 = lv_textarea_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_STextAreaHandicap2, 107);
    lv_obj_set_height(ui_STextAreaHandicap2, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_STextAreaHandicap2, 65);
    lv_obj_set_y(ui_STextAreaHandicap2, 180);
    lv_obj_set_align(ui_STextAreaHandicap2, LV_ALIGN_TOP_MID);
    lv_textarea_set_accepted_chars(ui_STextAreaHandicap2, "0123456789");
    lv_textarea_set_max_length(ui_STextAreaHandicap2, 3);
    lv_textarea_set_text(ui_STextAreaHandicap2, "0");
    lv_textarea_set_placeholder_text(ui_STextAreaHandicap2, "Фора...");
    lv_textarea_set_one_line(ui_STextAreaHandicap2, true);
    lv_obj_set_style_text_align(ui_STextAreaHandicap2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_SButtonEditHandicap2 = lv_btn_create(ui_SPanelSnooker);
    lv_obj_set_width(ui_SButtonEditHandicap2, 50);
    lv_obj_set_height(ui_SButtonEditHandicap2, 50);
    lv_obj_set_x(ui_SButtonEditHandicap2, 0);
    lv_obj_set_y(ui_SButtonEditHandicap2, 180);
    lv_obj_set_align(ui_SButtonEditHandicap2, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_SButtonEditHandicap2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditHandicap2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditHandicap2, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditHandicap2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditHandicap2 = lv_label_create(ui_SButtonEditHandicap2);
    lv_obj_set_width(ui_SLabelEditHandicap2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditHandicap2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditHandicap2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditHandicap2, LV_SYMBOL_EDIT);


    ui_SPanelOptions = lv_obj_create(ui_SPanelSettings);
    lv_obj_set_width(ui_SPanelOptions, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_align(ui_SPanelOptions, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_SPanelOptions, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SPanelOptions, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_SPanelOptions, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SPanelOptions, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SPanelOptions, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelOptions = lv_label_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SLabelOptions, lv_pct(100));
    lv_obj_set_height(ui_SLabelOptions, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelOptions, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_SLabelOptions, "Настройки");
    lv_obj_set_style_text_align(ui_SLabelOptions, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SPanelOptions1 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions1, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions1, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions1, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaGreeting = lv_textarea_create(ui_SPanelOptions1);
    lv_obj_set_width(ui_STextAreaGreeting, 265);
    lv_obj_set_height(ui_STextAreaGreeting, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaGreeting, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaGreeting, 128);
    lv_textarea_set_placeholder_text(ui_STextAreaGreeting, "Приветствие...");
    lv_textarea_set_one_line(ui_STextAreaGreeting, true);



    ui_SButtonEditGreeting = lv_btn_create(ui_SPanelOptions1);
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

    ui_SPanelOptions2 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions2, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions2, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions2, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaSSID = lv_textarea_create(ui_SPanelOptions2);
    lv_obj_set_width(ui_STextAreaSSID, 265);
    lv_obj_set_height(ui_STextAreaSSID, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaSSID, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaSSID, 32);
    lv_textarea_set_placeholder_text(ui_STextAreaSSID, "WiFi SSID...");
    lv_textarea_set_one_line(ui_STextAreaSSID, true);



    ui_SButtonEditSSID = lv_btn_create(ui_SPanelOptions2);
    lv_obj_set_width(ui_SButtonEditSSID, 50);
    lv_obj_set_height(ui_SButtonEditSSID, 50);
    lv_obj_set_align(ui_SButtonEditSSID, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditSSID, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditSSID, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditSSID, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditSSID = lv_label_create(ui_SButtonEditSSID);
    lv_obj_set_width(ui_SLabelEditSSID, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditSSID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditSSID, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditSSID, LV_SYMBOL_EDIT);

    ui_SPanelOptions3 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions3, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions3, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions3, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaWifiPass = lv_textarea_create(ui_SPanelOptions3);
    lv_obj_set_width(ui_STextAreaWifiPass, 265);
    lv_obj_set_height(ui_STextAreaWifiPass, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaWifiPass, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaWifiPass, 32);
    lv_textarea_set_placeholder_text(ui_STextAreaWifiPass, "WiFi пароль...");
    lv_textarea_set_one_line(ui_STextAreaWifiPass, true);
    lv_textarea_set_password_mode(ui_STextAreaWifiPass, true);



    ui_SButtonEditWifiPass = lv_btn_create(ui_SPanelOptions3);
    lv_obj_set_width(ui_SButtonEditWifiPass, 50);
    lv_obj_set_height(ui_SButtonEditWifiPass, 50);
    lv_obj_set_align(ui_SButtonEditWifiPass, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditWifiPass, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditWifiPass, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditWifiPass, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditWifiPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditWifiPass = lv_label_create(ui_SButtonEditWifiPass);
    lv_obj_set_width(ui_SLabelEditWifiPass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditWifiPass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditWifiPass, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditWifiPass, LV_SYMBOL_EDIT);

    ui_SPanelOptions4 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions4, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions4, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions4, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaTelegaChannel = lv_textarea_create(ui_SPanelOptions4);
    lv_obj_set_width(ui_STextAreaTelegaChannel, 265);
    lv_obj_set_height(ui_STextAreaTelegaChannel, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaTelegaChannel, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaTelegaChannel, 32);
    lv_textarea_set_placeholder_text(ui_STextAreaTelegaChannel, "Telegram канал...");
    lv_textarea_set_one_line(ui_STextAreaTelegaChannel, true);



    ui_SButtonEditTelegaChannel = lv_btn_create(ui_SPanelOptions4);
    lv_obj_set_width(ui_SButtonEditTelegaChannel, 50);
    lv_obj_set_height(ui_SButtonEditTelegaChannel, 50);
    lv_obj_set_align(ui_SButtonEditTelegaChannel, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditTelegaChannel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditTelegaChannel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditTelegaChannel, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditTelegaChannel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditTelegaChannel = lv_label_create(ui_SButtonEditTelegaChannel);
    lv_obj_set_width(ui_SLabelEditTelegaChannel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditTelegaChannel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditTelegaChannel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditTelegaChannel, LV_SYMBOL_EDIT);

    ui_SPanelOptions5 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions5, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions5, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions5, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions5, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaMqttHost = lv_textarea_create(ui_SPanelOptions5);
    lv_obj_set_width(ui_STextAreaMqttHost, 265);
    lv_obj_set_height(ui_STextAreaMqttHost, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaMqttHost, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaMqttHost, 64);
    lv_textarea_set_placeholder_text(ui_STextAreaMqttHost, "MQTT сервер...");
    lv_textarea_set_one_line(ui_STextAreaMqttHost, true);



    ui_SButtonEditMqttHost = lv_btn_create(ui_SPanelOptions5);
    lv_obj_set_width(ui_SButtonEditMqttHost, 50);
    lv_obj_set_height(ui_SButtonEditMqttHost, 50);
    lv_obj_set_align(ui_SButtonEditMqttHost, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditMqttHost, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditMqttHost, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditMqttHost, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditMqttHost, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditMqttHost = lv_label_create(ui_SButtonEditMqttHost);
    lv_obj_set_width(ui_SLabelEditMqttHost, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditMqttHost, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditMqttHost, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditMqttHost, LV_SYMBOL_EDIT);

    ui_SPanelOptions6 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions6, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions6, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions6, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions6, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaMqttPort = lv_textarea_create(ui_SPanelOptions6);
    lv_obj_set_width(ui_STextAreaMqttPort, 265);
    lv_obj_set_height(ui_STextAreaMqttPort, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaMqttPort, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaMqttPort, 5);
    lv_textarea_set_placeholder_text(ui_STextAreaMqttPort, "MQTT порт...");
    lv_textarea_set_one_line(ui_STextAreaMqttPort, true);



    ui_SButtonEditMqttPort = lv_btn_create(ui_SPanelOptions6);
    lv_obj_set_width(ui_SButtonEditMqttPort, 50);
    lv_obj_set_height(ui_SButtonEditMqttPort, 50);
    lv_obj_set_align(ui_SButtonEditMqttPort, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditMqttPort, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditMqttPort, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditMqttPort, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditMqttPort, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditMqttPort = lv_label_create(ui_SButtonEditMqttPort);
    lv_obj_set_width(ui_SLabelEditMqttPort, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditMqttPort, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditMqttPort, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditMqttPort, LV_SYMBOL_EDIT);

    ui_SPanelOptions7 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions7, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions7, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions7, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaMqttUser = lv_textarea_create(ui_SPanelOptions7);
    lv_obj_set_width(ui_STextAreaMqttUser, 265);
    lv_obj_set_height(ui_STextAreaMqttUser, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaMqttUser, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaMqttUser, 32);
    lv_textarea_set_placeholder_text(ui_STextAreaMqttUser, "MQTT логин...");
    lv_textarea_set_one_line(ui_STextAreaMqttUser, true);



    ui_SButtonEditMqttUser = lv_btn_create(ui_SPanelOptions7);
    lv_obj_set_width(ui_SButtonEditMqttUser, 50);
    lv_obj_set_height(ui_SButtonEditMqttUser, 50);
    lv_obj_set_align(ui_SButtonEditMqttUser, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditMqttUser, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditMqttUser, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditMqttUser, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditMqttUser, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditMqttUser = lv_label_create(ui_SButtonEditMqttUser);
    lv_obj_set_width(ui_SLabelEditMqttUser, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditMqttUser, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditMqttUser, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditMqttUser, LV_SYMBOL_EDIT);

    ui_SPanelOptions8 = lv_obj_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SPanelOptions8, lv_pct(100));
    lv_obj_set_height(ui_SPanelOptions8, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SPanelOptions8, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SPanelOptions8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SPanelOptions8, lv_color_hex(0x107B08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SPanelOptions8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_STextAreaMqttPass = lv_textarea_create(ui_SPanelOptions8);
    lv_obj_set_width(ui_STextAreaMqttPass, 265);
    lv_obj_set_height(ui_STextAreaMqttPass, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_STextAreaMqttPass, LV_ALIGN_LEFT_MID);
    lv_textarea_set_max_length(ui_STextAreaMqttPass, 32);
    lv_textarea_set_placeholder_text(ui_STextAreaMqttPass, "MQTT пароль...");
    lv_textarea_set_one_line(ui_STextAreaMqttPass, true);
    lv_textarea_set_password_mode(ui_STextAreaMqttPass, true);



    ui_SButtonEditMqttPass = lv_btn_create(ui_SPanelOptions8);
    lv_obj_set_width(ui_SButtonEditMqttPass, 50);
    lv_obj_set_height(ui_SButtonEditMqttPass, 50);
    lv_obj_set_align(ui_SButtonEditMqttPass, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_SButtonEditMqttPass, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonEditMqttPass, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonEditMqttPass, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonEditMqttPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelEditMqttPass = lv_label_create(ui_SButtonEditMqttPass);
    lv_obj_set_width(ui_SLabelEditMqttPass, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelEditMqttPass, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelEditMqttPass, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelEditMqttPass, LV_SYMBOL_EDIT);

    ui_SButtonSaveAll = lv_btn_create(ui_SPanelOptions);
    lv_obj_set_width(ui_SButtonSaveAll, lv_pct(100));
    lv_obj_set_height(ui_SButtonSaveAll, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_SButtonSaveAll, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_SButtonSaveAll, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SButtonSaveAll, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SButtonSaveAll, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SButtonSaveAll, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLabelSaveAll = lv_label_create(ui_SButtonSaveAll);
    lv_obj_set_width(ui_SLabelSaveAll, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLabelSaveAll, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SLabelSaveAll, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SLabelSaveAll, "Сохранить и Перезагрузить");

    ui_SOptionKeyboard = ui_OptionsKeyboard_create(ui_ScreenSettings);
    lv_obj_set_x(ui_SOptionKeyboard, 0);
    lv_obj_set_y(ui_SOptionKeyboard, 0);

}

static void ui_ScreenRestore_screen_init(void)
{
    ui_ScreenRestore = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenRestore, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_image_src(ui_ScreenRestore, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenRestore, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RLabelQuestion = lv_label_create(ui_ScreenRestore);
    lv_obj_set_width(ui_RLabelQuestion, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RLabelQuestion, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RLabelQuestion, -2);
    lv_obj_set_y(ui_RLabelQuestion, -47);
    lv_obj_set_align(ui_RLabelQuestion, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RLabelQuestion, "Восстановить счёт?");
    lv_obj_set_style_text_color(ui_RLabelQuestion, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RLabelQuestion, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RLabelWait = lv_label_create(ui_ScreenRestore);
    lv_obj_set_width(ui_RLabelWait, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RLabelWait, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RLabelWait, -100);
    lv_obj_set_y(ui_RLabelWait, 50);
    lv_obj_set_align(ui_RLabelWait, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RLabelWait, "Ожидайте....");
    lv_obj_set_style_text_color(ui_RLabelWait, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RLabelWait, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RButtonYes = lv_btn_create(ui_ScreenRestore);
    lv_obj_set_height(ui_RButtonYes, 50);
    lv_obj_set_width(ui_RButtonYes, lv_pct(40));
    lv_obj_set_x(ui_RButtonYes, 40);
    lv_obj_set_y(ui_RButtonYes, 50);
    lv_obj_set_align(ui_RButtonYes, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_RButtonYes, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_RButtonYes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_RButtonYes, lv_color_hex(0x0B4105), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RButtonYes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RLabelYes = lv_label_create(ui_RButtonYes);
    lv_obj_set_width(ui_RLabelYes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RLabelYes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_RLabelYes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RLabelYes, "Да");

    ui_RButtonCancel = lv_btn_create(ui_ScreenRestore);
    lv_obj_set_height(ui_RButtonCancel, 50);
    lv_obj_set_width(ui_RButtonCancel, lv_pct(40));
    lv_obj_set_x(ui_RButtonCancel, -40);
    lv_obj_set_y(ui_RButtonCancel, 50);
    lv_obj_set_align(ui_RButtonCancel, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_RButtonCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_RButtonCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_RButtonCancel, lv_color_hex(0x0B4105), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RButtonCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RLabelCancel = lv_label_create(ui_RButtonCancel);
    lv_obj_set_width(ui_RLabelCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RLabelCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_RLabelCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RLabelCancel, "Отмена");

}

///////////////////// FUNCTIONS ////////////////////

void gui_settings_create()
{
    ui_ScreenSettings_screen_init();

    // Load/Unload screen
    lv_obj_add_event_cb(ui_ScreenSettings, ui_event_ScreenSettings, LV_EVENT_ALL, NULL);

    // update board settings
    lv_obj_add_event_cb(ui_SSwitchAP, ui_event_SSwitchAP, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SSwitchWifi, ui_event_SSwitchWifi, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SSwitchTelega, ui_event_SSwitchTelega, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SSwitchAudio, ui_event_SSwitchAudio, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SSliderVolume, ui_event_SSliderVolume, LV_EVENT_ALL, NULL);

    // restore score
    lv_obj_add_event_cb(ui_SButtonRestore, ui_event_SButtonRestore, LV_EVENT_ALL, NULL);

    // go home screen
    lv_obj_add_event_cb(ui_SLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);

    // Edit Handicap
    lv_obj_add_event_cb(ui_SButtonEditHandicap1, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaHandicap1);
    lv_obj_add_event_cb(ui_SButtonEditHandicap2, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaHandicap2);

    // Edit options
    lv_obj_add_event_cb(ui_SButtonEditGreeting, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaGreeting);
    lv_obj_add_event_cb(ui_SButtonEditMqttHost, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaMqttHost);
    lv_obj_add_event_cb(ui_SButtonEditMqttPort, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaMqttPort);
    lv_obj_add_event_cb(ui_SButtonEditMqttPass, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaMqttPass);
    lv_obj_add_event_cb(ui_SButtonEditMqttUser, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaMqttUser);
    lv_obj_add_event_cb(ui_SButtonEditSSID, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaSSID);
    lv_obj_add_event_cb(ui_SButtonEditWifiPass, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaWifiPass);
    lv_obj_add_event_cb(ui_SButtonEditTelegaChannel, ui_event_onOptionEdit, LV_EVENT_ALL, ui_STextAreaTelegaChannel);

    // Save options
    lv_obj_add_event_cb(ui_SButtonSaveAll, ui_event_onOptionsSave, LV_EVENT_ALL, NULL);
}

void gui_restore_create()
{
    ui_ScreenRestore_screen_init();

    lv_obj_add_event_cb(ui_RButtonYes, ui_event_RButtonYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_RButtonCancel, ui_event_RButtonCancel, LV_EVENT_ALL, NULL);
}

