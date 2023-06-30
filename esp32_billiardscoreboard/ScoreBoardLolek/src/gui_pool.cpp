#include "gui_pool.h"
#include "gui_components.h"
#include "gui_main.h"

#include "TaskNetwork.h"
#include "TaskAudio.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t* ui_ScreenPool;
lv_obj_t* ui_PLabelHome;
lv_obj_t* ui_PLabelRefresh;
lv_obj_t* ui_PSwitchPlyCount;
lv_obj_t* ui_PLabel2;
lv_obj_t* ui_PLabel3;
lv_obj_t* ui_PPanelPool2;
lv_obj_t* ui_PanelPool2Ply1;
lv_obj_t* ui_PImageBreak;
lv_obj_t* ui_PanelPool2Ply2;
lv_obj_t* ui_PPanelPool3;
lv_obj_t* ui_PanelPool3Ply1;
lv_obj_t* ui_PanelPool3Ply2;
lv_obj_t* ui_PanelPool3Ply3;

lv_obj_t* ui_PNameKeyboard;

lv_obj_t* ui_MBPanelPool;
lv_obj_t* ui_MBLabelPoolResetQ;
lv_obj_t* ui_MBBtnPoolResetYes;
lv_obj_t* ui_MBLabelPoolResetYes;
lv_obj_t* ui_MBBtnPoolResetNo;
lv_obj_t* ui_MBLabelPoolResetNo;

extern volatile bool publishHistory;

static lv_timer_t* scoreTimer;

static int16_t pool2Ply1Score = 0;
static int16_t pool2Ply2Score = 0;
static int16_t pool3Ply1Score = 0;
static int16_t pool3Ply2Score = 0;
static int16_t pool3Ply3Score = 0;

///////////////////// FUNCTIONS ////////////////////

static void ui_switchBreak(lv_event_t* e)
{
    static uint16_t angle = 0;

    angle = (angle == 0) ? 1800 : 0;

    lv_img_set_angle(ui_PImageBreak, angle);
}

static void ui_hideScorePlusMinus(lv_timer_t* timer)
{
    _ui_flag_modify((lv_obj_t*)timer->user_data, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}

static void ui_event_ScreenPool(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        ui_PNameKeyboard = ui_NameKeyboard_create(ui_ScreenPool);
        lv_obj_set_x(ui_PNameKeyboard, 0);
        lv_obj_set_y(ui_PNameKeyboard, 0);
        lv_obj_add_flag(ui_PNameKeyboard, LV_OBJ_FLAG_HIDDEN);   /// Flags

    }
    else if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        lv_obj_del(ui_PNameKeyboard);
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
    lv_obj_t* target = lv_event_get_target(e);

    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        _ui_flag_modify(ui_PPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_PPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        _ui_flag_modify(ui_PPanelPool2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_PPanelPool3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

static void ui_event_PImageBreak(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_switchBreak(e);
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
        pool2Ply1Score = 0;
        pool2Ply2Score = 0;

        pool3Ply1Score = 0;
        pool3Ply2Score = 0;
        pool3Ply3Score = 0;

        lv_obj_t* scoreLabel;

        scoreLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        lv_label_set_text(scoreLabel, "0");

        scoreLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        lv_label_set_text(scoreLabel, "0");

        scoreLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        lv_label_set_text(scoreLabel, "0");

        scoreLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        lv_label_set_text(scoreLabel, "0");

        scoreLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        lv_label_set_text(scoreLabel, "0");

        publishHistory = true;

        sendTelegaMessage(T_POOL_MESSAGE, gui_pool_getScore());
        sendTelegaMessage(T_COMMAND, gui_pool_getPollQuestion());

        _ui_flag_modify(ui_MBPanelPool, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

///////////////////// SCREENS ////////////////////

static void ui_ScreenPool_screen_init(void)
{
    ui_ScreenPool = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenPool, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenPool, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_ScreenPool, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenPool, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenPool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenPool, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PLabelHome = lv_label_create(ui_ScreenPool);
    lv_obj_set_width(ui_PLabelHome, 60);
    lv_obj_set_height(ui_PLabelHome, 50);
    lv_obj_set_x(ui_PLabelHome, -200);
    lv_obj_set_y(ui_PLabelHome, 125);
    lv_obj_set_align(ui_PLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PLabelHome, LV_SYMBOL_HOME);
    lv_obj_add_flag(ui_PLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_PLabelHome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PLabelRefresh = lv_label_create(ui_ScreenPool);
    lv_obj_set_width(ui_PLabelRefresh, 60);
    lv_obj_set_height(ui_PLabelRefresh, 50);
    lv_obj_set_x(ui_PLabelRefresh, 200);
    lv_obj_set_y(ui_PLabelRefresh, 125);
    lv_obj_set_align(ui_PLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PLabelRefresh, LV_SYMBOL_REFRESH);
    lv_obj_add_flag(ui_PLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_PLabelRefresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PSwitchPlyCount = lv_switch_create(ui_ScreenPool);
    lv_obj_set_width(ui_PSwitchPlyCount, 64);
    lv_obj_set_height(ui_PSwitchPlyCount, 32);
    lv_obj_set_x(ui_PSwitchPlyCount, 0);
    lv_obj_set_y(ui_PSwitchPlyCount, 115);
    lv_obj_set_align(ui_PSwitchPlyCount, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_PSwitchPlyCount, lv_color_hex(0x836529), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PSwitchPlyCount, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PSwitchPlyCount, lv_color_hex(0x004C00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_PSwitchPlyCount, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_PSwitchPlyCount, lv_color_hex(0x004C00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PSwitchPlyCount, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PSwitchPlyCount, lv_color_hex(0x836529), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_PSwitchPlyCount, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    ui_PLabel2 = lv_label_create(ui_ScreenPool);
    lv_obj_set_width(ui_PLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PLabel2, -55);
    lv_obj_set_y(ui_PLabel2, 115);
    lv_obj_set_align(ui_PLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PLabel2, "2");

    ui_PLabel3 = lv_label_create(ui_ScreenPool);
    lv_obj_set_width(ui_PLabel3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PLabel3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PLabel3, 55);
    lv_obj_set_y(ui_PLabel3, 115);
    lv_obj_set_align(ui_PLabel3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PLabel3, "3");

    ui_PPanelPool2 = lv_obj_create(ui_ScreenPool);
    lv_obj_set_width(ui_PPanelPool2, 430);
    lv_obj_set_height(ui_PPanelPool2, 225);
    lv_obj_set_x(ui_PPanelPool2, 0);
    lv_obj_set_y(ui_PPanelPool2, 30);
    lv_obj_set_align(ui_PPanelPool2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_PPanelPool2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PPanelPool2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PPanelPool2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_PPanelPool2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelPool2Ply1 = ui_PanelPoolPlayer_create(ui_PPanelPool2);
    lv_obj_set_x(ui_PanelPool2Ply1, -125);
    lv_obj_set_y(ui_PanelPool2Ply1, 0);
    lv_label_set_text(ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), "Игрок 1");

    ui_PImageBreak = lv_img_create(ui_PPanelPool2);
    lv_img_set_src(ui_PImageBreak, &ui_img_break_png);
    lv_obj_set_width(ui_PImageBreak, 64);
    lv_obj_set_height(ui_PImageBreak, 128);
    lv_obj_set_align(ui_PImageBreak, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PImageBreak, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_PImageBreak, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_PImageBreak, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_PImageBreak, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelPool2Ply2 = ui_PanelPoolPlayer_create(ui_PPanelPool2);
    lv_obj_set_x(ui_PanelPool2Ply2, 125);
    lv_obj_set_y(ui_PanelPool2Ply2, 0);
    lv_label_set_text(ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), "Игрок 2");

    ui_PPanelPool3 = lv_obj_create(ui_ScreenPool);
    lv_obj_set_width(ui_PPanelPool3, 430);
    lv_obj_set_height(ui_PPanelPool3, 225);
    lv_obj_set_x(ui_PPanelPool3, 0);
    lv_obj_set_y(ui_PPanelPool3, 30);
    lv_obj_set_align(ui_PPanelPool3, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_PPanelPool3, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_PPanelPool3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PPanelPool3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PPanelPool3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_PPanelPool3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelPool3Ply1 = ui_PanelPoolPlayer_create(ui_PPanelPool3);
    lv_obj_set_width(ui_PanelPool3Ply1, 140);
    lv_obj_set_height(ui_PanelPool3Ply1, 220);
    lv_obj_set_x(ui_PanelPool3Ply1, -145);
    lv_obj_set_y(ui_PanelPool3Ply1, 0);
    lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), "Игрок 1");

    ui_PanelPool3Ply2 = ui_PanelPoolPlayer_create(ui_PPanelPool3);
    lv_obj_set_width(ui_PanelPool3Ply2, 140);
    lv_obj_set_height(ui_PanelPool3Ply2, 220);
    lv_obj_set_x(ui_PanelPool3Ply2, 0);
    lv_obj_set_y(ui_PanelPool3Ply2, 0);
    lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), "Игрок 2");

    ui_PanelPool3Ply3 = ui_PanelPoolPlayer_create(ui_PPanelPool3);
    lv_obj_set_width(ui_PanelPool3Ply3, 140);
    lv_obj_set_height(ui_PanelPool3Ply3, 220);
    lv_obj_set_x(ui_PanelPool3Ply3, 145);
    lv_obj_set_y(ui_PanelPool3Ply3, 0);
    lv_label_set_text(ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME), "Игрок 3");

    ui_MBPanelPool = lv_obj_create(ui_ScreenPool);
    lv_obj_set_width(ui_MBPanelPool, 430);
    lv_obj_set_height(ui_MBPanelPool, 225);
    lv_obj_set_x(ui_MBPanelPool, 0);
    lv_obj_set_y(ui_MBPanelPool, 30);
    lv_obj_set_align(ui_MBPanelPool, LV_ALIGN_TOP_MID);
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

}

///////////////////// EXPORT ////////////////////

void gui_pool_init()
{
    ui_ScreenPool_screen_init();

    lv_obj_add_event_cb(ui_ScreenPool, ui_event_ScreenPool, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PLabelHome, ui_event_onLabelHome, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PLabelRefresh, ui_event_onLabelReset, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PSwitchPlyCount, ui_event_PSwitchPlyCount, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PImageBreak, ui_event_PImageBreak, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_MBBtnPoolResetYes, ui_event_MB_ResetYes, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MBBtnPoolResetNo, ui_event_MB_ResetNo, LV_EVENT_ALL, NULL);
}

String gui_pool_getPollQuestion()
{
    const char escp[] = "\"";
    const char comma = ',';

    String msg = F("/sendPoll?question=И кто же победит?");
    msg += F("&options=[");

    lv_obj_t* plyLabel;

    if (lv_obj_has_flag(ui_PPanelPool2, LV_OBJ_FLAG_HIDDEN))
    {
        msg += escp;
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
        msg += escp;
        msg += comma;
        msg += escp;
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
        msg += escp;
        msg += comma;
        msg += escp;
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
        msg += escp;
    }
    else
    {
        msg += escp;
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
        msg += escp;
        msg += comma;
        msg += escp;
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
        msg += escp;
    }

    msg += F("]");

    return msg;
}

String gui_pool_getScore()
{
    String msg = F("МАТЧ:\n");

    lv_obj_t* plyLabel;

    if (lv_obj_has_flag(ui_PPanelPool2, LV_OBJ_FLAG_HIDDEN))
    {
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        msg += lv_label_get_text(plyLabel);
        msg += F(" - ");
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);

        msg += F("\n");

        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        msg += lv_label_get_text(plyLabel);
        msg += F(" - ");
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);

        msg += F("\n");

        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        msg += lv_label_get_text(plyLabel);
        msg += F(" - ");
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
    }
    else
    {
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        msg += lv_label_get_text(plyLabel);
        msg += F(" - ");
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);

        msg += F("\n");

        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
        msg += lv_label_get_text(plyLabel);
        msg += F(" - ");
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        msg += lv_label_get_text(plyLabel);
    }

    return msg;
}

String gui_pool_getHistory()
{
    String msg;

    const char delimiter[] = "~";

    lv_obj_t* plyLabel;

    plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE);
    msg += lv_label_get_text(plyLabel);
    msg += delimiter;

    return msg;
}

void gui_pool_restoreHistory(String& value, uint8_t idx)
{
    lv_obj_t* plyLabel;

    switch (idx)
    {
    case 0:
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, value.c_str());
        break;
    case 1:
        pool2Ply1Score = value.toInt();
        lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool2Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", pool2Ply1Score);
        break;
    case 2:
        plyLabel = ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, value.c_str());
        break;
    case 3:
        pool2Ply2Score = value.toInt();
        lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool2Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", pool2Ply2Score);
        break;
    case 4:
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, value.c_str());
        break;
    case 5:
        pool3Ply1Score = value.toInt();
        lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply1, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", pool3Ply1Score);
        break;
    case 6:
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, value.c_str());
        break;
    case 7:
        pool3Ply2Score = value.toInt();
        lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply2, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", pool3Ply2Score);
        break;
    case 8:
        plyLabel = ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME);
        lv_label_set_text(plyLabel, value.c_str());
        break;
    case 9:
        pool3Ply3Score = value.toInt();
        lv_label_set_text_fmt(ui_comp_get_child(ui_PanelPool3Ply3, UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE), "%d", pool3Ply3Score);
        break;
    default:
        break;
    }
}

void changeScore(lv_event_t* e)
{
    lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

    _ui_flag_modify(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE], LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

    scoreTimer = lv_timer_create(ui_hideScorePlusMinus, 3000, comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE]);

    lv_timer_set_repeat_count(scoreTimer, 1);
}

void changeScorePlus(lv_event_t* e)
{
    lv_timer_ready(scoreTimer);

    lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

    lv_obj_t* parent = comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER];

    if (parent == ui_PanelPool2Ply1)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", ++pool2Ply1Score);
    }
    else if (parent == ui_PanelPool2Ply2)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", ++pool2Ply2Score);
    }
    else if (parent == ui_PanelPool3Ply1)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", ++pool3Ply1Score);
    }
    else if (parent == ui_PanelPool3Ply2)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", ++pool3Ply2Score);
    }
    else if (parent == ui_PanelPool3Ply3)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", ++pool3Ply3Score);
    }

    if (parent == ui_PanelPool2Ply1 || parent == ui_PanelPool2Ply2)
    {
        ui_switchBreak(e);
        sayGameResult(pool2Ply1Score, pool2Ply2Score);
    }
    else
    {
        sayGameResult(pool3Ply1Score, pool3Ply2Score, pool3Ply3Score);
    }

    publishHistory = true;
    sendTelegaMessage(T_POOL_MESSAGE, gui_pool_getScore());
}

void changeScoreMinus(lv_event_t* e)
{
    lv_timer_ready(scoreTimer);

    lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

    lv_obj_t* parent = comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER];

    if (parent == ui_PanelPool2Ply1)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", --pool2Ply1Score);
    }
    else if (parent == ui_PanelPool2Ply2)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", --pool2Ply2Score);
    }
    else if (parent == ui_PanelPool3Ply1)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", --pool3Ply1Score);
    }
    else if (parent == ui_PanelPool3Ply2)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", --pool3Ply2Score);
    }
    else if (parent == ui_PanelPool3Ply3)
    {
        lv_label_set_text_fmt(comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE], "%d", --pool3Ply3Score);
    }

    if (parent == ui_PanelPool2Ply1 || parent == ui_PanelPool2Ply2)
    {
        ui_switchBreak(e);
        sayGameResult(pool2Ply1Score, pool2Ply2Score);
    }
    else
    {
        sayGameResult(pool3Ply1Score, pool3Ply2Score, pool3Ply3Score);
    }

    publishHistory = true;
    sendTelegaMessage(T_POOL_MESSAGE, gui_pool_getScore());
}

void changePlayerName(lv_event_t* e)
{
    lv_obj_t** comp_PanelPoolPlayer = (lv_obj_t**)lv_event_get_user_data(e);

    lv_obj_t* lb = comp_PanelPoolPlayer[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME];

    ui_comp_set_child(ui_PNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMELABEL, lb);

    lv_textarea_set_text(ui_comp_get_child(ui_PNameKeyboard, UI_COMP_NAMEKEYBOARD_NAMETEXTAREA), lv_label_get_text(lb));

    _ui_flag_modify(ui_PNameKeyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}
