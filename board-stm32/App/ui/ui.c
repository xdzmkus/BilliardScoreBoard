// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.3.4
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_Screen0(lv_event_t * e);
lv_obj_t * ui_Screen0;
lv_obj_t * ui_Time;
void ui_event_ball1(lv_event_t * e);
lv_obj_t * ui_ball1;
void ui_event_ball2(lv_event_t * e);
lv_obj_t * ui_ball2;
void ui_event_ball3(lv_event_t * e);
lv_obj_t * ui_ball3;
void ui_event_ball4(lv_event_t * e);
lv_obj_t * ui_ball4;
void ui_event_ball5(lv_event_t * e);
lv_obj_t * ui_ball5;
void ui_event_ball6(lv_event_t * e);
lv_obj_t * ui_ball6;
void ui_event_PanelRand(lv_event_t * e);
lv_obj_t * ui_PanelRand;
lv_obj_t * ui_LabelRandom;
void ui_event_LabelLeft(lv_event_t * e);
lv_obj_t * ui_LabelLeft;
void ui_event_LabelRight(lv_event_t * e);
lv_obj_t * ui_LabelRight;
void ui_event_Screen1(lv_event_t * e);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_Label1P;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label1M;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Label2P;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label2M;
lv_obj_t * ui_Switch;
void ui_event_Screen2(lv_event_t * e);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Panel3;
lv_obj_t * ui_Label3P;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label3M;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_Label4P;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label4M;
lv_obj_t * ui_Panel5;
lv_obj_t * ui_Label5P;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label5M;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
}
void ui_event_ball1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball1, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_ball2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball2, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_ball3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball3, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_ball4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball4, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_ball5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball5, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_ball6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_state_modify(ui_ball6, LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
        handleRandomBall(e);
    }
}
void ui_event_PanelRand(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        handleRandomBall(e);
    }
}
void ui_event_LabelLeft(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
}
void ui_event_LabelRight(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
}
void ui_event_Screen1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Screen0, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
}
void ui_event_Screen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Screen0, LV_SCR_LOAD_ANIM_NONE, 100, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen0_screen_init(void)
{
    ui_Screen0 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen0, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen0, lv_color_hex(0x28D1CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen0, lv_color_hex(0x03000E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen0, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen0, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time = lv_label_create(ui_Screen0);
    lv_obj_set_width(ui_Time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Time, 0);
    lv_obj_set_y(ui_Time, 20);
    lv_obj_set_align(ui_Time, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_Time, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Time, "0:00:00");
    lv_obj_add_flag(ui_Time, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_ball1 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball1, &ui_img_ball1_png);
    lv_obj_set_width(ui_ball1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball1, -125);
    lv_obj_set_y(ui_ball1, 0);
    lv_obj_set_align(ui_ball1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ball2 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball2, &ui_img_ball2_png);
    lv_obj_set_width(ui_ball2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball2, -75);
    lv_obj_set_y(ui_ball2, 0);
    lv_obj_set_align(ui_ball2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball2, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ball3 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball3, &ui_img_ball3_png);
    lv_obj_set_width(ui_ball3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball3, -25);
    lv_obj_set_y(ui_ball3, 0);
    lv_obj_set_align(ui_ball3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball3, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ball4 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball4, &ui_img_ball4_png);
    lv_obj_set_width(ui_ball4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball4, 25);
    lv_obj_set_y(ui_ball4, 0);
    lv_obj_set_align(ui_ball4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball4, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball4, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ball5 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball5, &ui_img_ball5_png);
    lv_obj_set_width(ui_ball5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball5, 75);
    lv_obj_set_y(ui_ball5, 0);
    lv_obj_set_align(ui_ball5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball5, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball5, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ball6 = lv_img_create(ui_Screen0);
    lv_img_set_src(ui_ball6, &ui_img_ball6_png);
    lv_obj_set_width(ui_ball6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ball6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ball6, 125);
    lv_obj_set_y(ui_ball6, 0);
    lv_obj_set_align(ui_ball6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ball6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ball6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_ball6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui_ball6, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_PanelRand = lv_obj_create(ui_Screen0);
    lv_obj_set_width(ui_PanelRand, 200);
    lv_obj_set_height(ui_PanelRand, 85);
    lv_obj_set_x(ui_PanelRand, 0);
    lv_obj_set_y(ui_PanelRand, -5);
    lv_obj_set_align(ui_PanelRand, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_PanelRand, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelRand, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelRand, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelRand, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelRand, lv_color_hex(0x0A6A7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelRand, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelRand, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelRandom = lv_label_create(ui_PanelRand);
    lv_obj_set_width(ui_LabelRandom, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelRandom, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelRandom, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelRandom, "");

    ui_LabelLeft = lv_label_create(ui_Screen0);
    lv_obj_set_width(ui_LabelLeft, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelLeft, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelLeft, 10);
    lv_obj_set_y(ui_LabelLeft, -25);
    lv_obj_set_align(ui_LabelLeft, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_LabelLeft, "<");
    lv_obj_add_flag(ui_LabelLeft, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_LabelLeft, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_LabelLeft, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelRight = lv_label_create(ui_Screen0);
    lv_obj_set_width(ui_LabelRight, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelRight, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelRight, -10);
    lv_obj_set_y(ui_LabelRight, -25);
    lv_obj_set_align(ui_LabelRight, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_LabelRight, ">");
    lv_obj_add_flag(ui_LabelRight, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_LabelRight, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ball1, ui_event_ball1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ball2, ui_event_ball2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ball3, ui_event_ball3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ball4, ui_event_ball4, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ball5, ui_event_ball5, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ball6, ui_event_ball6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PanelRand, ui_event_PanelRand, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_LabelLeft, ui_event_LabelLeft, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_LabelRight, ui_event_LabelRight, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen0, ui_event_Screen0, LV_EVENT_ALL, NULL);

}
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, lv_pct(50));
    lv_obj_set_height(ui_Panel1, lv_pct(100));
    lv_obj_set_align(ui_Panel1, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel1, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1P = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1P, lv_pct(50));
    lv_obj_set_height(ui_Label1P, lv_pct(30));
    lv_obj_set_align(ui_Label1P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label1P, "+");
    lv_obj_add_flag(ui_Label1P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label1 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1, lv_pct(95));
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label1, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label1, "0");

    ui_Label1M = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1M, lv_pct(50));
    lv_obj_set_height(ui_Label1M, lv_pct(30));
    lv_obj_set_align(ui_Label1M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label1M, "-");
    lv_obj_add_flag(ui_Label1M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel2, lv_pct(50));
    lv_obj_set_height(ui_Panel2, lv_pct(100));
    lv_obj_set_align(ui_Panel2, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel2, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2P = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2P, lv_pct(50));
    lv_obj_set_height(ui_Label2P, lv_pct(30));
    lv_obj_set_align(ui_Label2P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label2P, "+");
    lv_obj_add_flag(ui_Label2P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label2 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2, lv_pct(95));
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label2, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label2, "0");

    ui_Label2M = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2M, lv_pct(50));
    lv_obj_set_height(ui_Label2M, lv_pct(30));
    lv_obj_set_align(ui_Label2M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label2M, "-");
    lv_obj_add_flag(ui_Label2M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Switch = lv_switch_create(ui_Screen1);
    lv_obj_set_width(ui_Switch, 50);
    lv_obj_set_height(ui_Switch, 20);
    lv_obj_set_x(ui_Switch, 0);
    lv_obj_set_y(ui_Switch, 60);
    lv_obj_set_align(ui_Switch, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_Switch, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Switch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

}
void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Screen2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2, &ui_font_Ubuntu80Digits, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel3 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel3, lv_pct(33));
    lv_obj_set_height(ui_Panel3, lv_pct(100));
    lv_obj_set_align(ui_Panel3, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel3, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3P = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3P, lv_pct(50));
    lv_obj_set_height(ui_Label3P, lv_pct(30));
    lv_obj_set_align(ui_Label3P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label3P, "+");
    lv_obj_add_flag(ui_Label3P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label3 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3, lv_pct(95));
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label3, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label3, "0");

    ui_Label3M = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label3M, lv_pct(50));
    lv_obj_set_height(ui_Label3M, lv_pct(30));
    lv_obj_set_align(ui_Label3M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label3M, "-");
    lv_obj_add_flag(ui_Label3M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel4 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel4, lv_pct(33));
    lv_obj_set_height(ui_Panel4, lv_pct(100));
    lv_obj_set_align(ui_Panel4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel4, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel4, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel4, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel4, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4P = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4P, lv_pct(50));
    lv_obj_set_height(ui_Label4P, lv_pct(30));
    lv_obj_set_align(ui_Label4P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label4P, "+");
    lv_obj_add_flag(ui_Label4P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label4 = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4, lv_pct(95));
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label4, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label4, "0");

    ui_Label4M = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label4M, lv_pct(50));
    lv_obj_set_height(ui_Label4M, lv_pct(30));
    lv_obj_set_align(ui_Label4M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label4M, "-");
    lv_obj_add_flag(ui_Label4M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Panel5 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel5, lv_pct(33));
    lv_obj_set_height(ui_Panel5, lv_pct(100));
    lv_obj_set_align(ui_Panel5, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_Panel5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel5, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel5, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Panel5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Panel5, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel5, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5P = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5P, lv_pct(50));
    lv_obj_set_height(ui_Label5P, lv_pct(30));
    lv_obj_set_align(ui_Label5P, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label5P, "+");
    lv_obj_add_flag(ui_Label5P, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    ui_Label5 = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5, lv_pct(95));
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label5, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_Label5, "0");

    ui_Label5M = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5M, lv_pct(50));
    lv_obj_set_height(ui_Label5M, lv_pct(30));
    lv_obj_set_align(ui_Label5M, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label5M, "-");
    lv_obj_add_flag(ui_Label5M, LV_OBJ_FLAG_CLICKABLE);     /// Flags

    lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Screen0_screen_init();
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_Screen0);
}
