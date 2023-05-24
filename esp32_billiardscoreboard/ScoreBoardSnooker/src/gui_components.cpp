#include "gui_components.h"
#include "gui_pool.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

static const char ply_names[] = "Дима\nПаша\nИгорь\nСергей\nВова\nВиталик\nСаша\nДенис\nКристина\nНаташа\nЖеня\nВитя\nИлья";

uint32_t LV_EVENT_GET_COMP_CHILD;
uint32_t LV_EVENT_SET_COMP_CHILD;

typedef struct
{
    uint32_t child_idx;
    lv_obj_t * child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t * comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_event_send(comp, static_cast<lv_event_code_t>(LV_EVENT_GET_COMP_CHILD), &info);
    return info.child;
}

 void ui_comp_set_child(lv_obj_t* comp, uint32_t child_idx, lv_obj_t* obj)
{
    ui_comp_get_child_t info;
    info.child = obj;
    info.child_idx = child_idx;
    lv_event_send(comp, static_cast<lv_event_code_t>(LV_EVENT_SET_COMP_CHILD), &info);
}

void get_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t** c = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    ui_comp_get_child_t * info = static_cast<ui_comp_get_child_t*>(lv_event_get_param(e));
    info->child = c[info->child_idx];
}

void set_component_child_event_cb(lv_event_t* e)
{
    lv_obj_t** c = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    ui_comp_get_child_t* info = static_cast<ui_comp_get_child_t*>(lv_event_get_param(e));
    c[info->child_idx] = info->child;
}

void del_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    lv_mem_free(c);
}


// COMPONENT PanelPoolPlayer

static void ui_event_comp_PanelPoolPlayer_PanelPoolPlayer(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    //    lv_obj_t** comp_PanelPoolPlayer = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    if (event_code == LV_EVENT_CLICKED)
    {
        changeScore(e);
    }
}

void ui_event_comp_PanelPoolPlayer_LabelPoolPlyName(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
//    lv_obj_t** comp_PanelPoolPlayer = static_cast<lv_obj_t**>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        changePlayerName(e);
    }
}

static void ui_event_comp_PanelPoolPlayer_LabelPlus(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    //    lv_obj_t** comp_PanelPoolPlayer = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    if (event_code == LV_EVENT_CLICKED)
    {
        changeScorePlus(e);
    }
}

static void ui_event_comp_PanelPoolPlayer_LabelMinus(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    //    lv_obj_t* target = lv_event_get_target(e);
    //    lv_obj_t** comp_PanelPoolPlayer = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    if (event_code == LV_EVENT_CLICKED)
    {
        changeScoreMinus(e);
    }
}

lv_obj_t * ui_PanelPoolPlayer_create(lv_obj_t * comp_parent)
{
    lv_obj_t * cui_PanelPoolPlayer;
    cui_PanelPoolPlayer = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_PanelPoolPlayer, 180);
    lv_obj_set_height(cui_PanelPoolPlayer, 220);
    lv_obj_set_x(cui_PanelPoolPlayer, -125);
    lv_obj_set_y(cui_PanelPoolPlayer, 0);
    lv_obj_set_align(cui_PanelPoolPlayer, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_PanelPoolPlayer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_PanelPoolPlayer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_PanelPoolPlayer, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_PanelPoolPlayer, lv_color_hex(0x625020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_PanelPoolPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_PanelPoolPlayer, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_PanelPoolPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelPoolPlyScore;
    cui_LabelPoolPlyScore = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyScore, lv_pct(100));
    lv_obj_set_height(cui_LabelPoolPlyScore, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelPoolPlyScore, LV_ALIGN_CENTER);
    lv_label_set_long_mode(cui_LabelPoolPlyScore, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(cui_LabelPoolPlyScore, "0");
    lv_obj_set_style_text_color(cui_LabelPoolPlyScore, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_LabelPoolPlyScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(cui_LabelPoolPlyScore, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_LabelPoolPlyScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelPoolPlyChange;
    cui_LabelPoolPlyChange = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyChange, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_LabelPoolPlyChange, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelPoolPlyChange, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(cui_LabelPoolPlyChange, "...");

    lv_obj_t * cui_LabelPoolPlyName;
    cui_LabelPoolPlyName = lv_label_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_LabelPoolPlyName, lv_pct(100));
    lv_obj_set_height(cui_LabelPoolPlyName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelPoolPlyName, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(cui_LabelPoolPlyName, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(cui_LabelPoolPlyName, "Игрок");
    lv_obj_set_style_text_align(cui_LabelPoolPlyName, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(cui_LabelPoolPlyName, LV_OBJ_FLAG_CLICKABLE);   /// Flags

    lv_obj_t * cui_PanelPoolPlyScore;
    cui_PanelPoolPlyScore = lv_obj_create(cui_PanelPoolPlayer);
    lv_obj_set_width(cui_PanelPoolPlyScore, lv_pct(100));
    lv_obj_set_height(cui_PanelPoolPlyScore, lv_pct(100));
    lv_obj_set_align(cui_PanelPoolPlyScore, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_PanelPoolPlyScore, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(cui_PanelPoolPlyScore, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_PanelPoolPlyScore, lv_color_hex(0x105908), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_PanelPoolPlyScore, 225, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_PanelPoolPlyScore, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_PanelPoolPlyScore, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_PanelPoolPlyScore, &ui_font_UbuntuDigits92, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelPlus;
    cui_LabelPlus = lv_label_create(cui_PanelPoolPlyScore);
    lv_obj_set_width(cui_LabelPlus, lv_pct(100));
    lv_obj_set_height(cui_LabelPlus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelPlus, LV_ALIGN_TOP_MID);
    lv_label_set_text(cui_LabelPlus, "+");
    lv_obj_add_flag(cui_LabelPlus, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(cui_LabelPlus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_LabelMinus;
    cui_LabelMinus = lv_label_create(cui_PanelPoolPlyScore);
    lv_obj_set_width(cui_LabelMinus, lv_pct(100));
    lv_obj_set_height(cui_LabelMinus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelMinus, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(cui_LabelMinus, "-");
    lv_obj_add_flag(cui_LabelMinus, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(cui_LabelMinus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = static_cast<lv_obj_t**>(lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_PANELPOOLPLAYER_NUM));
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLAYER] = cui_PanelPoolPlayer;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYSCORE] = cui_LabelPoolPlyScore;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYCHANGE] = cui_LabelPoolPlyChange;
    children[UI_COMP_PANELPOOLPLAYER_LABELPOOLPLYNAME] = cui_LabelPoolPlyName;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE] = cui_PanelPoolPlyScore;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELPLUS] = cui_LabelPlus;
    children[UI_COMP_PANELPOOLPLAYER_PANELPOOLPLYSCORE_LABELMINUS] = cui_LabelMinus;
    lv_obj_add_event_cb(cui_PanelPoolPlayer, get_component_child_event_cb, static_cast<lv_event_code_t>(LV_EVENT_GET_COMP_CHILD), children);
    lv_obj_add_event_cb(cui_PanelPoolPlayer, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_LabelPoolPlyName, ui_event_comp_PanelPoolPlayer_LabelPoolPlyName, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_LabelPlus, ui_event_comp_PanelPoolPlayer_LabelPlus, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_LabelMinus, ui_event_comp_PanelPoolPlayer_LabelMinus, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_PanelPoolPlayer, ui_event_comp_PanelPoolPlayer_PanelPoolPlayer, LV_EVENT_ALL, children);
    return cui_PanelPoolPlayer;
}

// COMPONENT KeyboardPanel

#define LV_KB_BTN(width) LV_BTNMATRIX_CTRL_POPOVER | width

static const char* cyrillic_kb_map_lc[] = { "1#", "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ", LV_SYMBOL_BACKSPACE, "\n",
                                             LV_SYMBOL_UP, "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", LV_SYMBOL_NEW_LINE, "\n",
                                             "_", "-","я", "ч", "с", "м", "и", "т", "ь", "б", "ю", "ё", ".", ",", ":", "\n",
                                             LV_SYMBOL_KEYBOARD, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

static const lv_btnmatrix_ctrl_t cyrillic_kb_ctrl_lc_map[] = {
    LV_KEYBOARD_CTRL_BTN_FLAGS | 5, LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_BTNMATRIX_CTRL_CHECKED | 7,
    LV_KEYBOARD_CTRL_BTN_FLAGS | 6, LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_BTNMATRIX_CTRL_CHECKED | 7,
    LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BTN_FLAGS | 2, LV_BTNMATRIX_CTRL_CHECKED | 2, 6, LV_BTNMATRIX_CTRL_CHECKED | 2, LV_KEYBOARD_CTRL_BTN_FLAGS | 2
};

static const char* cyrillic_kb_map_uc[] = { "1#", "Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х", "Ъ", LV_SYMBOL_BACKSPACE, "\n",
                                             LV_SYMBOL_DOWN, "Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э", LV_SYMBOL_NEW_LINE, "\n",
                                             "_", "-","Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю", "Ё", ".", ",", ":", "\n",
                                             LV_SYMBOL_KEYBOARD, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

static const lv_btnmatrix_ctrl_t cyrillic_kb_ctrl_uc_map[] = {
    LV_KEYBOARD_CTRL_BTN_FLAGS | 5, LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_KB_BTN(4), LV_BTNMATRIX_CTRL_CHECKED | 7,
    LV_KEYBOARD_CTRL_BTN_FLAGS | 6, LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_KB_BTN(3), LV_BTNMATRIX_CTRL_CHECKED | 7,
    LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BTN_FLAGS | 2, LV_BTNMATRIX_CTRL_CHECKED | 2, 6, LV_BTNMATRIX_CTRL_CHECKED | 2, LV_KEYBOARD_CTRL_BTN_FLAGS | 2
};

static void ui_hide_component(lv_obj_t** comp)
{
    lv_textarea_set_text(comp[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA], "");

    lv_obj_add_flag(comp[UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD], LV_OBJ_FLAG_HIDDEN);
}

static void ui_event_comp_NameKeyboard_ButtonClose(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t** comp_KeyboardPanel = static_cast<lv_obj_t**>(lv_event_get_user_data(e));

    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
}

static void ui_event_comp_NameKeyboard_NameTextArea(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
//    lv_obj_t* target = lv_event_get_target(e);
    lv_obj_t** comp_KeyboardPanel = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    
    if (event_code == LV_EVENT_CANCEL)
    {
        ui_hide_component(comp_KeyboardPanel);
    }
    else if (event_code == LV_EVENT_READY)
    {
        if (comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMELABEL] != NULL)
        {
            lv_label_set_text(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMELABEL], lv_textarea_get_text(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA]));
            lv_event_send(comp_KeyboardPanel[UI_COMP_NAMEKEYBOARD_NAMELABEL], LV_EVENT_VALUE_CHANGED, NULL);
        }

        ui_hide_component(comp_KeyboardPanel);
    }
}

static void ui_event_comp_NameKeyboard_KeyboardButtons(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
//    lv_obj_t** comp_KeyboardPanel = static_cast<lv_obj_t**>(lv_event_get_user_data(e));
    
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        const char* txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

        if (txt == NULL) return;

        if (strcmp(txt, LV_SYMBOL_DOWN) == 0)
        {
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_1);
            return;
        }

        if (strcmp(txt, LV_SYMBOL_UP) == 0)
        {
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_2);
            return;
        }

        lv_keyboard_mode_t k_mode = lv_keyboard_get_mode(obj);

        if (strcmp(txt, LV_SYMBOL_KEYBOARD) == 0)
        {
            switch (k_mode)
            {
            case LV_KEYBOARD_MODE_USER_1:
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_TEXT_LOWER);
                return;
            case LV_KEYBOARD_MODE_USER_2:
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_TEXT_UPPER);
                return;
            case LV_KEYBOARD_MODE_TEXT_UPPER:
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_2);
                return;
            default:
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_1);
                return;
            }
        }

        lv_keyboard_def_event_cb(e);
    }
}

static void ui_event_comp_NameKeyboard_NameList(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    lv_obj_t** comp_KeyboardPanel = static_cast<lv_obj_t**>(lv_event_get_user_data(e));

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
    lv_obj_set_width(cui_NameKeyboard, lv_pct(90));
    lv_obj_set_height(cui_NameKeyboard, lv_pct(80));
    lv_obj_set_align(cui_NameKeyboard, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_NameKeyboard, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_NameKeyboard, lv_color_hex(0x105508), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_NameKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_NameKeyboard, &ui_font_UbuntuCyrillic25, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_NameList;
    cui_NameList = lv_dropdown_create(cui_NameKeyboard);
    lv_dropdown_set_options(cui_NameList, ply_names);
    lv_dropdown_set_text(cui_NameList, "Выбрать");
    lv_obj_set_width(cui_NameList, 150);
    lv_obj_set_height(cui_NameList, LV_SIZE_CONTENT);    /// 1
    lv_obj_add_flag(cui_NameList, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    lv_obj_t* cui_NameTextArea;
    cui_NameTextArea = lv_textarea_create(cui_NameKeyboard);
    lv_obj_set_width(cui_NameTextArea, 185);
    lv_obj_set_height(cui_NameTextArea, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_NameTextArea, -55);
    lv_obj_set_y(cui_NameTextArea, 0);
    lv_obj_set_align(cui_NameTextArea, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(cui_NameTextArea, 95);
    lv_textarea_set_placeholder_text(cui_NameTextArea, "Имя...");
    lv_textarea_set_one_line(cui_NameTextArea, true);

    lv_obj_t* cui_ButtonClose;
    cui_ButtonClose = lv_btn_create(cui_NameKeyboard);
    lv_obj_set_height(cui_ButtonClose, 50);
    lv_obj_set_width(cui_ButtonClose, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_align(cui_ButtonClose, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(cui_ButtonClose, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_ButtonClose, lv_color_hex(0x6A5529), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_ButtonClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* cui_LabelClose;
    cui_LabelClose = lv_label_create(cui_ButtonClose);
    lv_obj_set_width(cui_LabelClose, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_LabelClose, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_LabelClose, LV_ALIGN_CENTER);
    lv_label_set_text(cui_LabelClose, LV_SYMBOL_CLOSE);

    lv_obj_t* cui_KeyboardButtons;
    cui_KeyboardButtons = lv_keyboard_create(cui_NameKeyboard);
    lv_keyboard_set_mode(cui_KeyboardButtons, LV_KEYBOARD_MODE_TEXT_UPPER);
    lv_obj_set_width(cui_KeyboardButtons, lv_pct(100));
    lv_obj_set_height(cui_KeyboardButtons, lv_pct(70));
    lv_obj_set_align(cui_KeyboardButtons, LV_ALIGN_BOTTOM_MID);
    
    lv_keyboard_set_textarea(cui_KeyboardButtons, cui_NameTextArea);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_1, cyrillic_kb_map_lc, cyrillic_kb_ctrl_lc_map);
    lv_keyboard_set_map(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_2, cyrillic_kb_map_uc, cyrillic_kb_ctrl_uc_map);
    lv_keyboard_set_mode(cui_KeyboardButtons, LV_KEYBOARD_MODE_USER_2);
    lv_obj_remove_event_cb(cui_KeyboardButtons, lv_keyboard_def_event_cb);

    lv_obj_t** children = static_cast<lv_obj_t**>(lv_mem_alloc(sizeof(lv_obj_t*) * _UI_COMP_NAMEKEYBOARD_NUM));
    children[UI_COMP_NAMEKEYBOARD_NAMEKEYBOARD] = cui_NameKeyboard;
    children[UI_COMP_NAMEKEYBOARD_NAMELABEL] = NULL;
    children[UI_COMP_NAMEKEYBOARD_NAMELIST] = cui_NameList;
    children[UI_COMP_NAMEKEYBOARD_NAMETEXTAREA] = cui_NameTextArea;
    children[UI_COMP_NAMEKEYBOARD_BUTTONCLOSE] = cui_ButtonClose;
    children[UI_COMP_NAMEKEYBOARD_BUTTONCLOSE_LABELCLOSE] = cui_LabelClose;
    children[UI_COMP_NAMEKEYBOARD_KEYBOARDBUTTONS] = cui_KeyboardButtons;

    lv_obj_add_event_cb(cui_NameKeyboard, set_component_child_event_cb, static_cast<lv_event_code_t>(LV_EVENT_SET_COMP_CHILD), children);
    lv_obj_add_event_cb(cui_NameKeyboard, get_component_child_event_cb, static_cast<lv_event_code_t>(LV_EVENT_GET_COMP_CHILD), children);
    lv_obj_add_event_cb(cui_NameKeyboard, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_ButtonClose, ui_event_comp_NameKeyboard_ButtonClose, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_NameList, ui_event_comp_NameKeyboard_NameList, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_NameTextArea, ui_event_comp_NameKeyboard_NameTextArea, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_KeyboardButtons, ui_event_comp_NameKeyboard_KeyboardButtons, LV_EVENT_ALL, children);

    return cui_NameKeyboard;
}
