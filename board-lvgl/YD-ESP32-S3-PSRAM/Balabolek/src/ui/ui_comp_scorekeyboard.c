#include "ui_comp_scorekeyboard.h"

static void ui_hide_component(lv_obj_t** comp)
{
    lv_textarea_set_text(comp[UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE], "");

    lv_obj_add_flag(comp[UI_COMP_SCOREKEYBOARD_SCOREKEYBOARD], LV_OBJ_FLAG_HIDDEN);
}

static void ui_event_comp_ScoreKeyboard_ScoreTextArea(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CANCEL)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
    else if (event_code == LV_EVENT_READY)
    {
        ui_comp_cb_t cb = ui_comp_get_callback(comp_KeyboardPanel[UI_COMP_SCOREKEYBOARD_SCOREKEYBOARD]);
        
        if(cb != NULL)
        {
            cb(comp_KeyboardPanel[UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE]);
        }

        ui_hide_component(comp_KeyboardPanel);
    }
}

lv_obj_t * ui_ScoreKeyboard_create(lv_obj_t * comp_parent)
{
    lv_obj_t * cui_ScoreKeyboard;
    cui_ScoreKeyboard = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_ScoreKeyboard, lv_pct(100));
    lv_obj_set_height(cui_ScoreKeyboard, lv_pct(100));
    lv_obj_set_align(cui_ScoreKeyboard, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(cui_ScoreKeyboard, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(cui_ScoreKeyboard, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(cui_ScoreKeyboard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_ScoreKeyboard, lv_color_hex(0x1E5016), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_ScoreKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_ScoreKeyboard, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_ScoreKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_ScoreKeyboard, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_ScoreKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(cui_ScoreKeyboard, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelUpdatedScore;
    cui_LabelUpdatedScore = lv_label_create(cui_ScoreKeyboard);
    lv_obj_set_width(cui_LabelUpdatedScore, lv_pct(45));
    lv_obj_set_height(cui_LabelUpdatedScore, LV_SIZE_CONTENT);    /// 90
    lv_obj_set_x(cui_LabelUpdatedScore, 0);
    lv_obj_set_y(cui_LabelUpdatedScore, 5);
    lv_label_set_long_mode(cui_LabelUpdatedScore, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_font(cui_LabelUpdatedScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_TextAreaNewScore;
    cui_TextAreaNewScore = lv_textarea_create(cui_ScoreKeyboard);
    lv_obj_set_width(cui_TextAreaNewScore, lv_pct(55));
    lv_obj_set_height(cui_TextAreaNewScore, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(cui_TextAreaNewScore, 10);
    lv_obj_set_y(cui_TextAreaNewScore, -5);
    lv_obj_set_align(cui_TextAreaNewScore, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(cui_TextAreaNewScore, 5);
    lv_textarea_set_one_line(cui_TextAreaNewScore, true);
    lv_obj_set_style_text_align(cui_TextAreaNewScore, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_TextAreaNewScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_TextAreaNewScore, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_TextAreaNewScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_KeyboardScore;
    cui_KeyboardScore = lv_keyboard_create(cui_ScoreKeyboard);
    lv_obj_set_width(cui_KeyboardScore, lv_pct(105));
    lv_obj_set_height(cui_KeyboardScore, lv_pct(70));
    lv_obj_set_x(cui_KeyboardScore, 0);
    lv_obj_set_y(cui_KeyboardScore, 12);
    lv_obj_set_align(cui_KeyboardScore, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_radius(cui_KeyboardScore, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_KeyboardScore, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_KeyboardScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_KeyboardScore, &ui_font_UbuntuCyrillic25, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_keyboard_set_textarea(cui_KeyboardScore, cui_TextAreaNewScore);
	lv_keyboard_set_map(cui_KeyboardScore, LV_KEYBOARD_MODE_NUMBER, score_kb_map_num, score_kb_ctrl_num_map);
	lv_keyboard_set_mode(cui_KeyboardScore, LV_KEYBOARD_MODE_NUMBER);
	lv_obj_remove_event_cb(cui_KeyboardScore, lv_keyboard_def_event_cb);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_SCOREKEYBOARD_NUM);
    children[UI_COMP_SCOREKEYBOARD_SCOREKEYBOARD] = cui_ScoreKeyboard;
    children[UI_COMP_SCOREKEYBOARD_LABELUPDATEDSCORE] = cui_LabelUpdatedScore;
    children[UI_COMP_SCOREKEYBOARD_TEXTAREANEWSCORE] = cui_TextAreaNewScore;
    children[UI_COMP_SCOREKEYBOARD_KEYBOARDSCORE] = cui_KeyboardScore;

    lv_obj_add_event_cb(cui_ScoreKeyboard, set_component_child_event_cb, LV_EVENT_SET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_ScoreKeyboard, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_ScoreKeyboard, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_TextAreaNewScore, ui_event_comp_ScoreKeyboard_ScoreTextArea, LV_EVENT_ALL, children);
	lv_obj_add_event_cb(cui_KeyboardScore, ui_event_ScoreKeyboardButtons, LV_EVENT_ALL, children);

    ui_comp_cb_t* callback = lv_malloc(sizeof(ui_comp_cb_t));
    *callback = NULL;

    lv_obj_add_event_cb(cui_ScoreKeyboard, set_component_callback_event_cb, LV_EVENT_SET_COMP_CALLBACK, callback);
    lv_obj_add_event_cb(cui_ScoreKeyboard, get_component_callback_event_cb, LV_EVENT_GET_COMP_CALLBACK, callback);
    lv_obj_add_event_cb(cui_ScoreKeyboard, del_component_callback_event_cb, LV_EVENT_DELETE, callback);

    return cui_ScoreKeyboard;
}

