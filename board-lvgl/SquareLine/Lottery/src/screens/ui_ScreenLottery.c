// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Lottery

#include "../ui.h"

void ui_ScreenLottery_screen_init(void)
{
    ui_ScreenLottery = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScreenLottery, &ui_img_snooker_table_480x320_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ScreenLottery, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ScreenLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenLottery, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ScreenLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ScreenLottery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenLottery, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LLabelHome = lv_label_create(ui_ScreenLottery);
    lv_obj_set_width(ui_LLabelHome, 120);
    lv_obj_set_height(ui_LLabelHome, 50);
    lv_obj_set_x(ui_LLabelHome, -145);
    lv_obj_set_y(ui_LLabelHome, 125);
    lv_obj_set_align(ui_LLabelHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLabelHome, "#  Назад");
    lv_obj_add_flag(ui_LLabelHome, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_LLabelHome, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LLabelRefresh = lv_label_create(ui_ScreenLottery);
    lv_obj_set_width(ui_LLabelRefresh, 150);
    lv_obj_set_height(ui_LLabelRefresh, 50);
    lv_obj_set_x(ui_LLabelRefresh, 130);
    lv_obj_set_y(ui_LLabelRefresh, 125);
    lv_obj_set_align(ui_LLabelRefresh, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLabelRefresh, "Сбросить  #");
    lv_obj_add_flag(ui_LLabelRefresh, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_LLabelRefresh, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LRollerLots = lv_roller_create(ui_ScreenLottery);
    lv_roller_set_options(ui_LRollerLots,
                          "2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_LRollerLots, 200);
    lv_obj_set_width(ui_LRollerLots, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_LRollerLots, -175);
    lv_obj_set_y(ui_LRollerLots, -15);
    lv_obj_set_align(ui_LRollerLots, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_LRollerLots, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LRollerLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_LRollerLots, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_LRollerLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_LRollerLots, lv_color_hex(0x109108), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LRollerLots, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_LPanelLot = lv_obj_create(ui_ScreenLottery);
    lv_obj_set_width(ui_LPanelLot, 280);
    lv_obj_set_height(ui_LPanelLot, 200);
    lv_obj_set_x(ui_LPanelLot, 0);
    lv_obj_set_y(ui_LPanelLot, -15);
    lv_obj_set_align(ui_LPanelLot, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_LPanelLot, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_LPanelLot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_LPanelLot, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LPanelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_LPanelLot, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_LPanelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LLabelLot = lv_label_create(ui_LPanelLot);
    lv_obj_set_width(ui_LLabelLot, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LLabelLot, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LLabelLot, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLabelLot, "");
    lv_obj_set_style_text_color(ui_LLabelLot, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LLabelLot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LLabelLot, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LPanelLottery = lv_obj_create(ui_ScreenLottery);
    lv_obj_set_width(ui_LPanelLottery, 280);
    lv_obj_set_height(ui_LPanelLottery, 200);
    lv_obj_set_x(ui_LPanelLottery, 0);
    lv_obj_set_y(ui_LPanelLottery, -15);
    lv_obj_set_align(ui_LPanelLottery, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_LPanelLottery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_LPanelLottery, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LPanelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_LPanelLottery, lv_color_hex(0x665024), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_LPanelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LLabelLottery = lv_label_create(ui_LPanelLottery);
    lv_obj_set_width(ui_LLabelLottery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LLabelLottery, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LLabelLottery, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LLabelLottery, "Тянуть жребий");
    lv_obj_set_style_text_color(ui_LLabelLottery, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LLabelLottery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LPanelListLots = lv_obj_create(ui_ScreenLottery);
    lv_obj_set_width(ui_LPanelListLots, 65);
    lv_obj_set_height(ui_LPanelListLots, 200);
    lv_obj_set_x(ui_LPanelListLots, 175);
    lv_obj_set_y(ui_LPanelListLots, -15);
    lv_obj_set_align(ui_LPanelListLots, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_LPanelListLots, lv_color_hex(0x004C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_LPanelListLots, lv_color_hex(0x625020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_LPanelListLots, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LPanelListLots, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LLabelListLots = lv_label_create(ui_LPanelListLots);
    lv_obj_set_width(ui_LLabelListLots, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LLabelListLots, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LLabelListLots, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LLabelListLots, "");
    lv_obj_add_flag(ui_LLabelListLots, LV_OBJ_FLAG_CLICKABLE);     /// Flags

}