#include "ui_comp_optionskeyboard.h"

static void ui_hide_component(lv_obj_t** comp)
{
    lv_keyboard_set_mode(comp[UI_COMP_OPTIONSKEYBOARD_KEYBOARDBUTTONS], LV_KEYBOARD_MODE_TEXT_UPPER); // set ABC mode

    lv_obj_add_flag(comp[UI_COMP_OPTIONSKEYBOARD_OPTIONSKEYBOARD], LV_OBJ_FLAG_HIDDEN);
}

static void ui_event_comp_OptionsKeyboard_ButtonClose(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
}

static void ui_event_comp_OptionsKeyboard_OptionTextArea(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CANCEL)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
    else if (event_code == LV_EVENT_READY)
    {
        if (comp_KeyboardPanel[UI_COMP_OPTIONSKEYBOARD_EXPORTTEXTAREA] != NULL)
        {
            lv_textarea_set_text(comp_KeyboardPanel[UI_COMP_OPTIONSKEYBOARD_EXPORTTEXTAREA], lv_textarea_get_text(comp_KeyboardPanel[UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA]));
            lv_obj_send_event(comp_KeyboardPanel[UI_COMP_OPTIONSKEYBOARD_EXPORTTEXTAREA], LV_EVENT_VALUE_CHANGED, NULL);
        }

        ui_hide_component(comp_KeyboardPanel);
    }
}

lv_obj_t* ui_OptionsKeyboard_create(lv_obj_t* comp_parent)
{
    lv_obj_t * cui_OptionsKeyboard;
    cui_OptionsKeyboard = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_OptionsKeyboard, lv_pct(100));
    lv_obj_set_height(cui_OptionsKeyboard, lv_pct(100));
    lv_obj_set_align(cui_OptionsKeyboard, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_OptionsKeyboard, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(cui_OptionsKeyboard, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_OptionsKeyboard, lv_color_hex(0x105508), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_OptionsKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_OptionsKeyboard, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_OptionTextArea;
    cui_OptionTextArea = lv_textarea_create(cui_OptionsKeyboard);
    lv_obj_set_width(cui_OptionTextArea, lv_pct(85));
    lv_obj_set_height(cui_OptionTextArea, LV_SIZE_CONTENT);    /// 1
    lv_textarea_set_max_length(cui_OptionTextArea, 95);
    lv_textarea_set_one_line(cui_OptionTextArea, true);

    lv_obj_t * cui_ButtonClose;
    cui_ButtonClose = lv_btn_create(cui_OptionsKeyboard);
    lv_obj_set_height(cui_ButtonClose, 50);
    lv_obj_set_width(cui_ButtonClose, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_align(cui_ButtonClose, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_ButtonClose, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_ButtonClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelClose;
    cui_LabelClose = lv_label_create(cui_ButtonClose);
    lv_obj_set_width(cui_LabelClose, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_LabelClose, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelClose, LV_ALIGN_CENTER);
    lv_label_set_text(cui_LabelClose, LV_SYMBOL_CLOSE);

    lv_obj_t * cui_KeyboardButtons;
    cui_KeyboardButtons = lv_keyboard_create(cui_OptionsKeyboard);
    lv_obj_set_width(cui_KeyboardButtons, lv_pct(100));
    lv_obj_set_height(cui_KeyboardButtons, lv_pct(75));
    lv_obj_set_align(cui_KeyboardButtons, LV_ALIGN_BOTTOM_MID);

    lv_keyboard_set_textarea(cui_KeyboardButtons, cui_OptionTextArea);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_UPPER, latin_kb_map_uc, latin_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_LOWER, latin_kb_map_lc, latin_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_SPECIAL, special_kb_map, special_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_1, cyrillic_kb_map_lc, cyrillic_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_2, cyrillic_kb_map_uc, cyrillic_kb_ctrl_map);
    lv_keyboard_set_mode(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_UPPER);
    lv_obj_set_style_text_font(cui_KeyboardButtons, &ui_font_UbuntuCyrillic25, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_remove_event_cb(cui_KeyboardButtons, lv_keyboard_def_event_cb);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_OPTIONSKEYBOARD_NUM);
    children[UI_COMP_OPTIONSKEYBOARD_OPTIONSKEYBOARD] = cui_OptionsKeyboard;
    children[UI_COMP_OPTIONSKEYBOARD_OPTIONTEXTAREA] = cui_OptionTextArea;
    children[UI_COMP_OPTIONSKEYBOARD_BUTTONCLOSE] = cui_ButtonClose;
    children[UI_COMP_OPTIONSKEYBOARD_BUTTONCLOSE_LABELCLOSE] = cui_LabelClose;
    children[UI_COMP_OPTIONSKEYBOARD_KEYBOARDBUTTONS] = cui_KeyboardButtons;
    children[UI_COMP_OPTIONSKEYBOARD_EXPORTTEXTAREA] = NULL;
   
    lv_obj_add_event_cb(cui_OptionsKeyboard, set_component_child_event_cb, LV_EVENT_SET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_OptionsKeyboard, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_OptionsKeyboard, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_ButtonClose, ui_event_comp_OptionsKeyboard_ButtonClose, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_OptionTextArea, ui_event_comp_OptionsKeyboard_OptionTextArea, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_KeyboardButtons, ui_event_KeyboardButtons, LV_EVENT_ALL, children);

   return cui_OptionsKeyboard;
}
