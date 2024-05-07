#include "ui_comp_panelpoolplayer.h"

extern void changeName(lv_event_t* e);
extern void changeScore(lv_event_t* e);
extern void changeScorePlus(lv_event_t* e);
extern void changeScoreMinus(lv_event_t* e);


static void ui_event_comp_PanelPoolPlayer_PanelPoolPlayer(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        changeName(e);
    }
    else if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        changeScore(e);
    }
}

static void ui_event_comp_PanelPoolPlayer_LabelPlus(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        changeScorePlus(e);
    }
}

static void ui_event_comp_PanelPoolPlayer_LabelMinus(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        changeScoreMinus(e);
    }
}

lv_obj_t* ui_PanelPoolPlayer_create(lv_obj_t* comp_parent)
{
    lv_obj_t* cui_PanelPoolPlayer;
    cui_PanelPoolPlayer = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_PanelPoolPlayer, 180);
    lv_obj_set_height(cui_PanelPoolPlayer, 220);
    lv_obj_set_x(cui_PanelPoolPlayer, -125);
    lv_obj_set_y(cui_PanelPoolPlayer, 0);
    lv_obj_set_align(cui_PanelPoolPlayer, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_PanelPoolPlayer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(cui_PanelPoolPlayer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_PanelPoolPlayer, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_PanelPoolPlayer, lv_color_hex(0x625020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_PanelPoolPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_PanelPoolPlayer, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_PanelPoolPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelPoolPlyScore;
    cui_LabelPoolPlyScore = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyScore, lv_pct(100));
    lv_obj_set_height(cui_LabelPoolPlyScore, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelPoolPlyScore, LV_ALIGN_CENTER);
    lv_label_set_long_mode(cui_LabelPoolPlyScore, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(cui_LabelPoolPlyScore, "0");
    lv_obj_set_style_text_color(cui_LabelPoolPlyScore, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_LabelPoolPlyScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(cui_LabelPoolPlyScore, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_LabelPoolPlyScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelPoolPlyChange;
    cui_LabelPoolPlyChange = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyChange, LV_SIZE_CONTENT);
    lv_obj_set_height(cui_LabelPoolPlyChange, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelPoolPlyChange, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(cui_LabelPoolPlyChange, "...");

    lv_obj_t* cui_LabelPoolPlyName;
    cui_LabelPoolPlyName = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyName, lv_pct(100));
    lv_obj_set_height(cui_LabelPoolPlyName, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelPoolPlyName, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(cui_LabelPoolPlyName, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(cui_LabelPoolPlyName, "Игрок");
    lv_obj_set_style_text_align(cui_LabelPoolPlyName, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_PanelPoolPlyScore;
    cui_PanelPoolPlyScore = lv_obj_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_PanelPoolPlyScore, lv_pct(100));
    lv_obj_set_height(cui_PanelPoolPlyScore, lv_pct(100));
    lv_obj_set_align(cui_PanelPoolPlyScore, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_PanelPoolPlyScore, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(cui_PanelPoolPlyScore, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(cui_PanelPoolPlyScore, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_PanelPoolPlyScore, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_PanelPoolPlyScore, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_PanelPoolPlyScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_PanelPoolPlyScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelPlus;
    cui_LabelPlus = lv_label_create(cui_PanelPoolPlyScore);
    lv_obj_set_width(cui_LabelPlus, lv_pct(100));
    lv_obj_set_height(cui_LabelPlus, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelPlus, LV_ALIGN_TOP_MID);
    lv_label_set_text(cui_LabelPlus, "+");
    lv_obj_add_flag(cui_LabelPlus, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_align(cui_LabelPlus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelMinus;
    cui_LabelMinus = lv_label_create(cui_PanelPoolPlyScore);
    lv_obj_set_width(cui_LabelMinus, lv_pct(100));
    lv_obj_set_height(cui_LabelMinus, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelMinus, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(cui_LabelMinus, "-");
    lv_obj_add_flag(cui_LabelMinus, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_align(cui_LabelMinus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t** children = lv_malloc(sizeof(lv_obj_t*) * _UI_COMP_PANELPOOLPLAYER_NUM);
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER] = cui_PanelPoolPlayer;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE] = cui_LabelPoolPlyScore;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYCHANGE] = cui_LabelPoolPlyChange;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME] = cui_LabelPoolPlyName;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE] = cui_PanelPoolPlyScore;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELPLUS] = cui_LabelPlus;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELMINUS] = cui_LabelMinus;
    lv_obj_add_event_cb(cui_PanelPoolPlayer, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_PanelPoolPlayer, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_LabelPlus, ui_event_comp_PanelPoolPlayer_LabelPlus, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_LabelMinus, ui_event_comp_PanelPoolPlayer_LabelMinus, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_PanelPoolPlayer, ui_event_comp_PanelPoolPlayer_PanelPoolPlayer, LV_EVENT_ALL, children);

    return cui_PanelPoolPlayer;
}

