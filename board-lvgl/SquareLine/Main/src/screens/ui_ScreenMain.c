// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Main

#include "../ui.h"

void ui_ScreenMain_screen_init(void)
{
    ui_ScreenMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenMain, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenMain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenMain, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MLabelLogo = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelLogo, 400);
    lv_obj_set_height(ui_MLabelLogo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelLogo, 0);
    lv_obj_set_y(ui_MLabelLogo, 40);
    lv_obj_set_align(ui_MLabelLogo, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_MLabelLogo, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_MLabelLogo, "https://t.me");
    lv_obj_set_style_text_align(ui_MLabelLogo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnDarts = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnDarts, 190);
    lv_obj_set_height(ui_MBtnDarts, 50);
    lv_obj_set_x(ui_MBtnDarts, -100);
    lv_obj_set_y(ui_MBtnDarts, -40);
    lv_obj_set_align(ui_MBtnDarts, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnDarts, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnDarts, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnDarts, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelDarts = lv_label_create(ui_MBtnDarts);
    lv_obj_set_width(ui_MBtnLabelDarts, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelDarts, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelDarts, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelDarts, "Дартс");

    ui_MBtnLottery = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnLottery, 190);
    lv_obj_set_height(ui_MBtnLottery, 50);
    lv_obj_set_x(ui_MBtnLottery, 100);
    lv_obj_set_y(ui_MBtnLottery, -40);
    lv_obj_set_align(ui_MBtnLottery, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnLottery, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelLottery = lv_label_create(ui_MBtnLottery);
    lv_obj_set_width(ui_MBtnLabelLottery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelLottery, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelLottery, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelLottery, "Жребий");

    ui_MBtnGame = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnGame, 150);
    lv_obj_set_height(ui_MBtnGame, 50);
    lv_obj_set_x(ui_MBtnGame, -120);
    lv_obj_set_y(ui_MBtnGame, 25);
    lv_obj_set_align(ui_MBtnGame, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnGame, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnGame, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnGame, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnGame, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelGame = lv_label_create(ui_MBtnGame);
    lv_obj_set_width(ui_MBtnLabelGame, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelGame, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelGame, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelGame, "Игра");

    ui_MBtnStream = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnStream, 50);
    lv_obj_set_height(ui_MBtnStream, 50);
    lv_obj_set_x(ui_MBtnStream, 0);
    lv_obj_set_y(ui_MBtnStream, 25);
    lv_obj_set_align(ui_MBtnStream, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnStream, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnStream, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MBtnStream, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MBtnStream, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnStream, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_MBtnStream, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_MBtnStream, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelStream = lv_label_create(ui_MBtnStream);
    lv_obj_set_width(ui_MBtnLabelStream, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelStream, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelStream, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelStream, "TV");

    ui_MBtnSnooker = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSnooker, 150);
    lv_obj_set_height(ui_MBtnSnooker, 50);
    lv_obj_set_x(ui_MBtnSnooker, 120);
    lv_obj_set_y(ui_MBtnSnooker, 25);
    lv_obj_set_align(ui_MBtnSnooker, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBtnSnooker, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBtnSnooker, lv_color_hex(0x054E01), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBtnSnooker, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBtnLabelSnooker = lv_label_create(ui_MBtnSnooker);
    lv_obj_set_width(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBtnLabelSnooker, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MBtnLabelSnooker, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBtnLabelSnooker, "Снукер");

    ui_MBtnSettings = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_MBtnSettings, 190);
    lv_obj_set_height(ui_MBtnSettings, 50);
    lv_obj_set_x(ui_MBtnSettings, 100);
    lv_obj_set_y(ui_MBtnSettings, 90);
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

    ui_MLabelWifi = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelWifi, -160);
    lv_obj_set_y(ui_MLabelWifi, 90);
    lv_obj_set_align(ui_MLabelWifi, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelWifi, "#");
    lv_obj_set_style_text_color(ui_MLabelWifi, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_opa(ui_MLabelWifi, 255, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_decor(ui_MLabelWifi, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);

    ui_MLabelTelega = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelTelega, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelTelega, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelTelega, -100);
    lv_obj_set_y(ui_MLabelTelega, 90);
    lv_obj_set_align(ui_MLabelTelega, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelTelega, "#");
    lv_obj_set_style_text_color(ui_MLabelTelega, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_opa(ui_MLabelTelega, 255, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_decor(ui_MLabelTelega, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);

    ui_MLabelAudio = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_MLabelAudio, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MLabelAudio, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MLabelAudio, -40);
    lv_obj_set_y(ui_MLabelAudio, 90);
    lv_obj_set_align(ui_MLabelAudio, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MLabelAudio, "#");
    lv_obj_set_style_text_color(ui_MLabelAudio, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_opa(ui_MLabelAudio, 255, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_decor(ui_MLabelAudio, LV_TEXT_DECOR_STRIKETHROUGH, LV_PART_MAIN | LV_STATE_DISABLED);

}