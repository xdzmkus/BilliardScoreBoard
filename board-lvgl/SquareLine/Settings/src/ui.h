// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Settings

#ifndef _SQUARELINE_SETTINGS_UI_H
#define _SQUARELINE_SETTINGS_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"

// SCREEN: ui_ScreenSettings
void ui_ScreenSettings_screen_init(void);
extern lv_obj_t * ui_ScreenSettings;
extern lv_obj_t * ui_SLabelHome;
extern lv_obj_t * ui_SPanelSettings;
void ui_event_SButtonRestore(lv_event_t * e);
extern lv_obj_t * ui_SButtonRestore;
extern lv_obj_t * ui_SLabelRestore;
extern lv_obj_t * ui_SPanelGeneral;
extern lv_obj_t * ui_SLabelWifi;
extern lv_obj_t * ui_SSwitchWifi;
extern lv_obj_t * ui_SLabelTelega;
extern lv_obj_t * ui_SSwitchTelega;
extern lv_obj_t * ui_SLabelAudio;
extern lv_obj_t * ui_SSwitchAudio;
extern lv_obj_t * ui_SLabelVolume;
extern lv_obj_t * ui_SSliderVolume;
extern lv_obj_t * ui_SLabelAP;
extern lv_obj_t * ui_SSwitchAP;
extern lv_obj_t * ui_SPanelSnooker;
extern lv_obj_t * ui_SLabelSnooker;
extern lv_obj_t * ui_SLabel6Red;
extern lv_obj_t * ui_SSwitch6Red;
extern lv_obj_t * ui_SLabelControlBalls;
extern lv_obj_t * ui_SSwitchControlBalls;
extern lv_obj_t * ui_SLabekHandicap1;
extern lv_obj_t * ui_SLabekHandicapValue1;
extern lv_obj_t * ui_SButtonEditHandicap1;
extern lv_obj_t * ui_SLabelEditHandicap1;
extern lv_obj_t * ui_SLabekHandicap2;
extern lv_obj_t * ui_SLabekHandicapValue2;
extern lv_obj_t * ui_SButtonEditHandicap2;
extern lv_obj_t * ui_SLabelEditHandicap2;
extern lv_obj_t * ui_SPanelOptions;
extern lv_obj_t * ui_SLabelOptions;
extern lv_obj_t * ui_SPanelOptions1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_SButtonEditGreeting;
extern lv_obj_t * ui_SLabelEditGreeting;
extern lv_obj_t * ui_SPanelOptions2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_SButtonEditSSID;
extern lv_obj_t * ui_SLabelEditSSID;
extern lv_obj_t * ui_SPanelOptions3;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_SButtonEditWifiPass;
extern lv_obj_t * ui_SLabelEditWifiPass;
extern lv_obj_t * ui_SPanelOptions4;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_SButtonEditTelegaChannel;
extern lv_obj_t * ui_SLabelEditTelegaChannel;
extern lv_obj_t * ui_SPanelOptions5;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_SButtonEditMqttHost;
extern lv_obj_t * ui_SLabelEditMqttHost;
extern lv_obj_t * ui_SPanelOptions6;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_SButtonEditMqttPort;
extern lv_obj_t * ui_SLabelEditMqttPort;
extern lv_obj_t * ui_SPanelOptions7;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_SButtonEditMqttUser;
extern lv_obj_t * ui_SLabelEditMqttUser;
extern lv_obj_t * ui_SPanelOptions8;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_SButtonEditMqttPass;
extern lv_obj_t * ui_SLabelEditMqttPass;
extern lv_obj_t * ui_SButtonSaveAll;
extern lv_obj_t * ui_SLabelSaveAll;
extern lv_obj_t * ui_SOptionKeyboard;
// SCREEN: ui_ScreenRestore
void ui_ScreenRestore_screen_init(void);
extern lv_obj_t * ui_ScreenRestore;
extern lv_obj_t * ui_RLabelQuestion;
extern lv_obj_t * ui_RLabelWait;
void ui_event_RButtonYes(lv_event_t * e);
extern lv_obj_t * ui_RButtonYes;
extern lv_obj_t * ui_RLabelYes;
void ui_event_RButtonCancel(lv_event_t * e);
extern lv_obj_t * ui_RButtonCancel;
extern lv_obj_t * ui_RLabelCancel;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_snooker_table_480x320_png);    // assets/snooker_table_480x320.png



LV_FONT_DECLARE(ui_font_UbuntuCyrillic25);
LV_FONT_DECLARE(ui_font_UbuntuDigits92);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif