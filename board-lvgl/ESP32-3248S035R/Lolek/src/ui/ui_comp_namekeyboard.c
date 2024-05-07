#include "ui_comp_namekeyboard.h"

static const char ply_names[] = "Александр\nАлексей\nАндрей\nВадим\nВиктор\nВиталий\nВладимир\nДенис\nДмитрий\nЕвгений\nИгорь\nИлья\nКонстантин\nКристина\nНаталья\nПавел\nРенат\nРоман\nСергей\nТатьяна\nЮрий\n";

static void ui_hide_component(lv_obj_t** comp)
{
    lv_textarea_set_text(comp[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA], ""); // clear textarea

    lv_keyboard_set_mode(comp[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS], LV_KEYBOARD_MODE_USER_2); // set ABC mode

    lv_obj_add_flag(comp[UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD], LV_OBJ_FLAG_HIDDEN);
}

static void ui_event_comp_NameKeyboard_ButtonClose(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
}

static void ui_event_comp_NameKeyboard_NameTextArea(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CANCEL)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
    else if (event_code == LV_EVENT_READY)
    {
        ui_comp_cb_t cb = ui_comp_get_callback(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD]);
        
        if(cb != NULL)
        {
            cb(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA]);
        }

        ui_hide_component(comp_KeyboardPanel);
    }
    else if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        /*  Auto lower case */
        int textLen = strlen(lv_textarea_get_text(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA]));

        if (textLen == 1) /* ascii */
        {
            if (lv_keyboard_get_mode(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS]) == LV_KEYBOARD_MODE_TEXT_UPPER)
                lv_keyboard_set_mode(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS], LV_KEYBOARD_MODE_TEXT_LOWER);
        }
        else if (textLen == 2) /* wide symbols */
        {
            if (lv_keyboard_get_mode(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS]) == LV_KEYBOARD_MODE_USER_2)
                lv_keyboard_set_mode(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS], LV_KEYBOARD_MODE_USER_1);
        }
    }
}

static void ui_event_comp_NameKeyboard_NameList(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* obj = (lv_obj_t*)(lv_event_get_target(e));
    lv_obj_t** comp_KeyboardPanel = (lv_event_get_user_data(e));

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        lv_textarea_set_text(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA], buf);
    }
}

lv_obj_t* ui_NameKeyboard_create(lv_obj_t* comp_parent)
{
    lv_obj_t* cui_NameKeyboard;
    cui_NameKeyboard = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_NameKeyboard, lv_pct(100));
    lv_obj_set_height(cui_NameKeyboard, lv_pct(100));
    lv_obj_set_align(cui_NameKeyboard, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_NameKeyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(cui_NameKeyboard, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(cui_NameKeyboard, lv_color_hex(0x105508), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_NameKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_NameKeyboard, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_NameList;
    cui_NameList = lv_dropdown_create(cui_NameKeyboard);
    lv_dropdown_set_options(cui_NameList, ply_names);
    lv_dropdown_set_text(cui_NameList, "Выбрать");
    lv_obj_set_width(cui_NameList, 150);
    lv_obj_set_height(cui_NameList, LV_SIZE_CONTENT);
    lv_obj_add_flag(cui_NameList, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_t* cui_NameTextArea;
    cui_NameTextArea = lv_textarea_create(cui_NameKeyboard);
    lv_obj_set_width(cui_NameTextArea, 230);
    lv_obj_set_height(cui_NameTextArea, LV_SIZE_CONTENT);
    lv_obj_set_x(cui_NameTextArea, -55);
    lv_obj_set_y(cui_NameTextArea, 0);
    lv_obj_set_align(cui_NameTextArea, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(cui_NameTextArea, 95);
    lv_textarea_set_placeholder_text(cui_NameTextArea, "Имя...");
    lv_textarea_set_one_line(cui_NameTextArea, true);

    lv_obj_t* cui_ButtonClose;
    cui_ButtonClose = lv_btn_create(cui_NameKeyboard);
    lv_obj_set_height(cui_ButtonClose, 50);
    lv_obj_set_width(cui_ButtonClose, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_ButtonClose, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(cui_ButtonClose, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_ButtonClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelClose;
    cui_LabelClose = lv_label_create(cui_ButtonClose);
    lv_obj_set_width(cui_LabelClose, LV_SIZE_CONTENT);
    lv_obj_set_height(cui_LabelClose, LV_SIZE_CONTENT);
    lv_obj_set_align(cui_LabelClose, LV_ALIGN_CENTER);
    lv_label_set_text(cui_LabelClose, LV_SYMBOL_CLOSE);

    lv_obj_t* cui_KeyboardButtons;
    cui_KeyboardButtons = lv_keyboard_create(cui_NameKeyboard);
    lv_obj_set_width(cui_KeyboardButtons, lv_pct(100));
    lv_obj_set_height(cui_KeyboardButtons, lv_pct(75));
    lv_obj_set_align(cui_KeyboardButtons, LV_ALIGN_BOTTOM_MID);

    lv_keyboard_set_textarea(cui_KeyboardButtons, cui_NameTextArea);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_UPPER, latin_kb_map_uc, latin_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_LOWER, latin_kb_map_lc, latin_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_SPECIAL, special_kb_map, special_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_1, cyrillic_kb_map_lc, cyrillic_kb_ctrl_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_2, cyrillic_kb_map_uc, cyrillic_kb_ctrl_map);
    lv_keyboard_set_mode(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_2);
    lv_obj_set_style_text_font(cui_KeyboardButtons, &ui_font_UbuntuCyrillic25, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_remove_event_cb(cui_KeyboardButtons, lv_keyboard_def_event_cb);

    lv_obj_t** children = (lv_malloc(sizeof(lv_obj_t*) * _UI_COMP_NAMEKEYBOARD_NUM));
    children[UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD] = cui_NameKeyboard;
    children[UI_COMP_NAMEKEYBOARD_NAMELIST] = cui_NameList;
    children[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA] = cui_NameTextArea;
    children[UI_COMP_NAMEKEYBOARD_BUTTONCLOSE] = cui_ButtonClose;
    children[UI_COMP_NAMEKEYBOARD_BUTTONCLOSE_LABELCLOSE] = cui_LabelClose;
    children[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS] = cui_KeyboardButtons;

    lv_obj_add_event_cb(cui_NameKeyboard, set_component_child_event_cb, LV_EVENT_SET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_NameKeyboard, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_NameKeyboard, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_ButtonClose, ui_event_comp_NameKeyboard_ButtonClose, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_NameList, ui_event_comp_NameKeyboard_NameList, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_NameTextArea, ui_event_comp_NameKeyboard_NameTextArea, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_KeyboardButtons, ui_event_KeyboardButtons, LV_EVENT_ALL, children);

    ui_comp_cb_t* callback = lv_malloc(sizeof(ui_comp_cb_t));
    *callback = NULL;

    lv_obj_add_event_cb(cui_NameKeyboard, set_component_callback_event_cb, LV_EVENT_SET_COMP_CALLBACK, callback);
    lv_obj_add_event_cb(cui_NameKeyboard, get_component_callback_event_cb, LV_EVENT_GET_COMP_CALLBACK, callback);
    lv_obj_add_event_cb(cui_NameKeyboard, del_component_callback_event_cb, LV_EVENT_DELETE, callback);

    return cui_NameKeyboard;
}
