#include "gui_balls.h"
#include "gui_snooker.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

lv_obj_t* ui_ScreenBalls;
lv_obj_t* ui_BPanelBalls;
lv_obj_t* ui_BButtonRed;
lv_obj_t* ui_BLabel1;
lv_obj_t* ui_BButtonBlack;
lv_obj_t* ui_BLabel7;
lv_obj_t* ui_BButtonPink;
lv_obj_t* ui_BLabel6;
lv_obj_t* ui_BButtonBlue;
lv_obj_t* ui_BLabel5;
lv_obj_t* ui_BButtonBrown;
lv_obj_t* ui_BLabel4;
lv_obj_t* ui_BButtonGreen;
lv_obj_t* ui_BLabel3;
lv_obj_t* ui_BButtonYellow;
lv_obj_t* ui_BLabel2;
lv_obj_t* ui_BButtonMiss;
lv_obj_t* ui_BLabel0;
lv_obj_t* ui_BButtonFoul;
lv_obj_t* ui_BLabelFoul;
lv_obj_t* ui_BButtonFreeBall;
lv_obj_t* ui_BLabelFreeBall;
lv_obj_t* ui_BButtonCancel;
lv_obj_t* ui_BLabelCancel;
lv_obj_t* ui_BPanelFree;
lv_obj_t* ui_BButtonRedF;
lv_obj_t* ui_BLabelFB1;
lv_obj_t* ui_BButtonYellowF;
lv_obj_t* ui_BLabelFB2;
lv_obj_t* ui_BButtonGreenF;
lv_obj_t* ui_BLabelFB3;
lv_obj_t* ui_BButtonBrownF;
lv_obj_t* ui_BLabelFB4;
lv_obj_t* ui_BButtonBlueF;
lv_obj_t* ui_BLabelFB5;
lv_obj_t* ui_BButtonPinkF;
lv_obj_t* ui_BLabelFB6;
lv_obj_t* ui_BPanelFoul;
lv_obj_t* ui_BButtonF4;
lv_obj_t* ui_BLabelF4;
lv_obj_t* ui_BButtonF5;
lv_obj_t* ui_BLabelF5;
lv_obj_t* ui_BButtonF6;
lv_obj_t* ui_BLabelF6;
lv_obj_t* ui_BButtonF7;
lv_obj_t* ui_BLabelF7;
lv_obj_t* ui_BButtonF1;
lv_obj_t* ui_BLabelF1;

///////////////////// FUNCTIONS ////////////////////

static void ui_event_ScreenBalls(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        if (gui_snooker_isFreeBallPossible())
        {
            lv_obj_clear_state(ui_BButtonFreeBall, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonFreeBall, LV_STATE_DISABLED);
        }

        if (gui_snooker_isRedBallPossible())
        {
            lv_obj_clear_state(ui_BButtonRed, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonRedF, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonF1, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonRed, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonRedF, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonF1, LV_STATE_DISABLED);
        }

        if (gui_snooker_isYellowBallPossible())
        {
            lv_obj_clear_state(ui_BButtonYellow, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonYellowF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonYellow, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonYellowF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isGreenBallPossible())
        {
            lv_obj_clear_state(ui_BButtonGreen, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonGreenF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonGreen, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonGreenF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBrownBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBrown, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonBrownF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBrown, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonBrownF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBlueBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBlue, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonBlueF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBlue, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonBlueF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isPinkBallPossible())
        {
            lv_obj_clear_state(ui_BButtonPink, LV_STATE_DISABLED);
            lv_obj_clear_state(ui_BButtonPinkF, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonPink, LV_STATE_DISABLED);
            lv_obj_add_state(ui_BButtonPinkF, LV_STATE_DISABLED);
        }

        if (gui_snooker_isBlackBallPossible())
        {
            lv_obj_clear_state(ui_BButtonBlack, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(ui_BButtonBlack, LV_STATE_DISABLED);
        }
        
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BButtonFoul(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BButtonFreeBall(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_flag_modify(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

static void ui_event_BButtonCancel(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_ScreenSnooker, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}

static void ui_event_BBallAction(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (ui_BButtonMiss == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_MISS : P2_MISS);
        }
        else if (ui_BButtonRed == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_RED : P2_RED);
        }
        else if (ui_BButtonBlack == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BLACK : P2_BLACK);
        }
        else if (ui_BButtonPink == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_PINK : P2_PINK);
        }
        else if (ui_BButtonBlue == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BLUE : P2_BLUE);
        }
        else if (ui_BButtonBrown == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_BROWN : P2_BROWN);
        }
        else if (ui_BButtonGreen == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_GREEN : P2_GREEN);
        }
        else if (ui_BButtonYellow == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_YELLOW : P2_YELLOW);
        }
        else if (ui_BButtonRedF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_RED : P2_F_RED);
        }
        else if (ui_BButtonPinkF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_PINK : P2_F_PINK);
        }
        else if (ui_BButtonBlueF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_BLUE : P2_F_BLUE);
        }
        else if (ui_BButtonBrownF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_BROWN : P2_F_BROWN);
        }
        else if (ui_BButtonGreenF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_GREEN : P2_F_GREEN);
        }
        else if (ui_BButtonYellowF == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_F_YELLOW : P2_F_YELLOW);
        }
        else if (ui_BButtonF4 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_4 : P2_FOUL_4);
        }
        else if (ui_BButtonF5 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_5 : P2_FOUL_5);
        }
        else if (ui_BButtonF6 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_6 : P2_FOUL_6);
        }
        else if (ui_BButtonF7 == target)
        {
            gui_snooker_pushAction(gui_snooker_get_activePlayer() == PLAYER1 ? P1_FOUL_7 : P2_FOUL_7);
        }
        else if (ui_BButtonF1 == target)
        {
            gui_snooker_pushAction(P_FLUKE_RED);
        }

        _ui_screen_change(ui_ScreenSnooker, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}

///////////////////// SCREENS ////////////////////

void ui_ScreenBalls_screen_init(void)
{
    ui_ScreenBalls = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenBalls, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenBalls, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenBalls, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenBalls, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenBalls, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BPanelBalls = lv_obj_create(ui_ScreenBalls);
    lv_obj_set_width(ui_BPanelBalls, 430);
    lv_obj_set_height(ui_BPanelBalls, 260);
    lv_obj_set_x(ui_BPanelBalls, 0);
    lv_obj_set_y(ui_BPanelBalls, 30);
    lv_obj_set_align(ui_BPanelBalls, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_BPanelBalls, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelBalls, lv_color_hex(0x157207), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelBalls, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelBalls, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelBalls, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonRed = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonRed, 60);
    lv_obj_set_height(ui_BButtonRed, 60);
    lv_obj_set_x(ui_BButtonRed, -160);
    lv_obj_set_y(ui_BButtonRed, -85);
    lv_obj_set_align(ui_BButtonRed, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonRed, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonRed, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonRed, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonRed, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonRed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonRed, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonRed, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel1 = lv_label_create(ui_BButtonRed);
    lv_obj_set_width(ui_BLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel1, "1");

    ui_BButtonBlack = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBlack, 60);
    lv_obj_set_height(ui_BButtonBlack, 60);
    lv_obj_set_x(ui_BButtonBlack, 55);
    lv_obj_set_y(ui_BButtonBlack, 0);
    lv_obj_set_align(ui_BButtonBlack, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlack, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlack, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlack, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlack, lv_color_hex(0x6A6A6A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlack, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_BButtonBlack, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_BButtonBlack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlack, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel7 = lv_label_create(ui_BButtonBlack);
    lv_obj_set_width(ui_BLabel7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel7, "7");

    ui_BButtonPink = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonPink, 60);
    lv_obj_set_height(ui_BButtonPink, 60);
    lv_obj_set_x(ui_BButtonPink, -55);
    lv_obj_set_y(ui_BButtonPink, 0);
    lv_obj_set_align(ui_BButtonPink, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonPink, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonPink, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonPink, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonPink, lv_color_hex(0xEE89E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonPink, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonPink, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonPink, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel6 = lv_label_create(ui_BButtonPink);
    lv_obj_set_width(ui_BLabel6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel6, "6");

    ui_BButtonBlue = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBlue, 60);
    lv_obj_set_height(ui_BButtonBlue, 60);
    lv_obj_set_x(ui_BButtonBlue, -160);
    lv_obj_set_y(ui_BButtonBlue, 0);
    lv_obj_set_align(ui_BButtonBlue, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlue, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlue, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlue, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlue, lv_color_hex(0x0800FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlue, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlue, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel5 = lv_label_create(ui_BButtonBlue);
    lv_obj_set_width(ui_BLabel5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel5, "5");

    ui_BButtonBrown = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonBrown, 60);
    lv_obj_set_height(ui_BButtonBrown, 60);
    lv_obj_set_x(ui_BButtonBrown, 160);
    lv_obj_set_y(ui_BButtonBrown, -85);
    lv_obj_set_align(ui_BButtonBrown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBrown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBrown, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBrown, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBrown, lv_color_hex(0xA09200), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBrown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBrown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBrown, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel4 = lv_label_create(ui_BButtonBrown);
    lv_obj_set_width(ui_BLabel4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel4, "4");

    ui_BButtonGreen = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonGreen, 60);
    lv_obj_set_height(ui_BButtonGreen, 60);
    lv_obj_set_x(ui_BButtonGreen, 55);
    lv_obj_set_y(ui_BButtonGreen, -85);
    lv_obj_set_align(ui_BButtonGreen, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonGreen, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonGreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonGreen, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonGreen, lv_color_hex(0x3AFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonGreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonGreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonGreen, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel3 = lv_label_create(ui_BButtonGreen);
    lv_obj_set_width(ui_BLabel3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel3, "3");

    ui_BButtonYellow = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonYellow, 60);
    lv_obj_set_height(ui_BButtonYellow, 60);
    lv_obj_set_x(ui_BButtonYellow, -55);
    lv_obj_set_y(ui_BButtonYellow, -85);
    lv_obj_set_align(ui_BButtonYellow, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonYellow, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonYellow, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonYellow, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonYellow, lv_color_hex(0xF4FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonYellow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonYellow, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonYellow, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel2 = lv_label_create(ui_BButtonYellow);
    lv_obj_set_width(ui_BLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel2, "2");

    ui_BButtonMiss = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonMiss, 60);
    lv_obj_set_height(ui_BButtonMiss, 60);
    lv_obj_set_x(ui_BButtonMiss, 160);
    lv_obj_set_y(ui_BButtonMiss, 0);
    lv_obj_set_align(ui_BButtonMiss, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonMiss, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonMiss, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonMiss, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonMiss, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonMiss, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonMiss, lv_color_hex(0x848484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonMiss, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabel0 = lv_label_create(ui_BButtonMiss);
    lv_obj_set_width(ui_BLabel0, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabel0, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabel0, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabel0, "#000000 0#");
    lv_label_set_recolor(ui_BLabel0, "true");

    ui_BButtonFoul = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonFoul, 100);
    lv_obj_set_height(ui_BButtonFoul, 65);
    lv_obj_set_x(ui_BButtonFoul, 35);
    lv_obj_set_y(ui_BButtonFoul, 85);
    lv_obj_set_align(ui_BButtonFoul, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonFoul, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonFoul, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonFoul, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonFoul, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFoul = lv_label_create(ui_BButtonFoul);
    lv_obj_set_width(ui_BLabelFoul, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFoul, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFoul, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFoul, "Фол");

    ui_BButtonFreeBall = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonFreeBall, 165);
    lv_obj_set_height(ui_BButtonFreeBall, 65);
    lv_obj_set_x(ui_BButtonFreeBall, -110);
    lv_obj_set_y(ui_BButtonFreeBall, 85);
    lv_obj_set_align(ui_BButtonFreeBall, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonFreeBall, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonFreeBall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonFreeBall, lv_color_hex(0x1E3E02), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonFreeBall, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonFreeBall, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFreeBall = lv_label_create(ui_BButtonFreeBall);
    lv_obj_set_width(ui_BLabelFreeBall, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFreeBall, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFreeBall, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFreeBall, "Свободный\nшар");

    ui_BButtonCancel = lv_btn_create(ui_BPanelBalls);
    lv_obj_set_width(ui_BButtonCancel, 110);
    lv_obj_set_height(ui_BButtonCancel, 65);
    lv_obj_set_x(ui_BButtonCancel, 150);
    lv_obj_set_y(ui_BButtonCancel, 85);
    lv_obj_set_align(ui_BButtonCancel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonCancel, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BButtonCancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelCancel = lv_label_create(ui_BButtonCancel);
    lv_obj_set_width(ui_BLabelCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelCancel, "Отмена");

    ui_BPanelFree = lv_obj_create(ui_ScreenBalls);
    lv_obj_set_width(ui_BPanelFree, 400);
    lv_obj_set_height(ui_BPanelFree, 160);
    lv_obj_set_x(ui_BPanelFree, 0);
    lv_obj_set_y(ui_BPanelFree, -40);
    lv_obj_set_align(ui_BPanelFree, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BPanelFree, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_BPanelFree, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelFree, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelFree, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonRedF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonRedF, 60);
    lv_obj_set_height(ui_BButtonRedF, 60);
    lv_obj_set_x(ui_BButtonRedF, -120);
    lv_obj_set_y(ui_BButtonRedF, -40);
    lv_obj_set_align(ui_BButtonRedF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonRedF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonRedF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonRedF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonRedF, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonRedF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonRedF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonRedF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB1 = lv_label_create(ui_BButtonRedF);
    lv_obj_set_width(ui_BLabelFB1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB1, "1");

    ui_BButtonYellowF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonYellowF, 60);
    lv_obj_set_height(ui_BButtonYellowF, 60);
    lv_obj_set_x(ui_BButtonYellowF, 0);
    lv_obj_set_y(ui_BButtonYellowF, -40);
    lv_obj_set_align(ui_BButtonYellowF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonYellowF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonYellowF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonYellowF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonYellowF, lv_color_hex(0xF4FC63), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonYellowF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonYellowF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonYellowF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB2 = lv_label_create(ui_BButtonYellowF);
    lv_obj_set_width(ui_BLabelFB2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB2, "2");

    ui_BButtonGreenF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonGreenF, 60);
    lv_obj_set_height(ui_BButtonGreenF, 60);
    lv_obj_set_x(ui_BButtonGreenF, 120);
    lv_obj_set_y(ui_BButtonGreenF, -40);
    lv_obj_set_align(ui_BButtonGreenF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonGreenF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonGreenF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonGreenF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonGreenF, lv_color_hex(0x3AFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonGreenF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonGreenF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonGreenF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB3 = lv_label_create(ui_BButtonGreenF);
    lv_obj_set_width(ui_BLabelFB3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB3, "3");

    ui_BButtonBrownF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonBrownF, 60);
    lv_obj_set_height(ui_BButtonBrownF, 60);
    lv_obj_set_x(ui_BButtonBrownF, -120);
    lv_obj_set_y(ui_BButtonBrownF, 40);
    lv_obj_set_align(ui_BButtonBrownF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBrownF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBrownF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBrownF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBrownF, lv_color_hex(0x736902), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBrownF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBrownF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBrownF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB4 = lv_label_create(ui_BButtonBrownF);
    lv_obj_set_width(ui_BLabelFB4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB4, "4");

    ui_BButtonBlueF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonBlueF, 60);
    lv_obj_set_height(ui_BButtonBlueF, 60);
    lv_obj_set_x(ui_BButtonBlueF, 0);
    lv_obj_set_y(ui_BButtonBlueF, 40);
    lv_obj_set_align(ui_BButtonBlueF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonBlueF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonBlueF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonBlueF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonBlueF, lv_color_hex(0x0800FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonBlueF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonBlueF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonBlueF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB5 = lv_label_create(ui_BButtonBlueF);
    lv_obj_set_width(ui_BLabelFB5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB5, "5");

    ui_BButtonPinkF = lv_btn_create(ui_BPanelFree);
    lv_obj_set_width(ui_BButtonPinkF, 60);
    lv_obj_set_height(ui_BButtonPinkF, 60);
    lv_obj_set_x(ui_BButtonPinkF, 120);
    lv_obj_set_y(ui_BButtonPinkF, 40);
    lv_obj_set_align(ui_BButtonPinkF, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonPinkF, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonPinkF, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BButtonPinkF, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BButtonPinkF, lv_color_hex(0xEE89E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonPinkF, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BButtonPinkF, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BButtonPinkF, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelFB6 = lv_label_create(ui_BButtonPinkF);
    lv_obj_set_width(ui_BLabelFB6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelFB6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelFB6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelFB6, "6");

    ui_BPanelFoul = lv_obj_create(ui_ScreenBalls);
    lv_obj_set_width(ui_BPanelFoul, 400);
    lv_obj_set_height(ui_BPanelFoul, 160);
    lv_obj_set_x(ui_BPanelFoul, 0);
    lv_obj_set_y(ui_BPanelFoul, -40);
    lv_obj_set_align(ui_BPanelFoul, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BPanelFoul, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_BPanelFoul, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BPanelFoul, lv_color_hex(0x183C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BPanelFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BPanelFoul, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BPanelFoul, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BButtonF4 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF4, 100);
    lv_obj_set_height(ui_BButtonF4, 50);
    lv_obj_set_x(ui_BButtonF4, -130);
    lv_obj_set_y(ui_BButtonF4, -35);
    lv_obj_set_align(ui_BButtonF4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF4, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF4 = lv_label_create(ui_BButtonF4);
    lv_obj_set_width(ui_BLabelF4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF4, "+4");

    ui_BButtonF5 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF5, 100);
    lv_obj_set_height(ui_BButtonF5, 50);
    lv_obj_set_x(ui_BButtonF5, 0);
    lv_obj_set_y(ui_BButtonF5, -35);
    lv_obj_set_align(ui_BButtonF5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF5, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF5 = lv_label_create(ui_BButtonF5);
    lv_obj_set_width(ui_BLabelF5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF5, "+5");

    ui_BButtonF6 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF6, 100);
    lv_obj_set_height(ui_BButtonF6, 50);
    lv_obj_set_x(ui_BButtonF6, 130);
    lv_obj_set_y(ui_BButtonF6, -35);
    lv_obj_set_align(ui_BButtonF6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF6, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF6 = lv_label_create(ui_BButtonF6);
    lv_obj_set_width(ui_BLabelF6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF6, "+6");

    ui_BButtonF7 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF7, 100);
    lv_obj_set_height(ui_BButtonF7, 50);
    lv_obj_set_x(ui_BButtonF7, -130);
    lv_obj_set_y(ui_BButtonF7, 35);
    lv_obj_set_align(ui_BButtonF7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF7, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF7 = lv_label_create(ui_BButtonF7);
    lv_obj_set_width(ui_BLabelF7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF7, "+7");

    ui_BButtonF1 = lv_btn_create(ui_BPanelFoul);
    lv_obj_set_width(ui_BButtonF1, 230);
    lv_obj_set_height(ui_BButtonF1, 50);
    lv_obj_set_x(ui_BButtonF1, 65);
    lv_obj_set_y(ui_BButtonF1, 35);
    lv_obj_set_align(ui_BButtonF1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BButtonF1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BButtonF1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BButtonF1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BButtonF1, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLabelF1 = lv_label_create(ui_BButtonF1);
    lv_obj_set_width(ui_BLabelF1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLabelF1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_BLabelF1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLabelF1, "Упал красный");

    lv_obj_add_event_cb(ui_BButtonFoul, ui_event_BButtonFoul, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonFreeBall, ui_event_BButtonFreeBall, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonCancel, ui_event_BButtonCancel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenBalls, ui_event_ScreenBalls, LV_EVENT_ALL, NULL);

}

void gui_balls_init()
{
    ui_ScreenBalls_screen_init();

    lv_obj_add_event_cb(ui_ScreenBalls, ui_event_ScreenBalls, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonFoul, ui_event_BButtonFoul, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonFreeBall, ui_event_BButtonFreeBall, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonCancel, ui_event_BButtonCancel, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_BButtonMiss, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonRed, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlack, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonPink, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlue, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBrown, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonGreen, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonYellow, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonRedF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonPinkF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBlueF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonBrownF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonGreenF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonYellowF, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF4, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF5, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF6, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF7, ui_event_BBallAction, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BButtonF1, ui_event_BBallAction, LV_EVENT_ALL, NULL);

}
