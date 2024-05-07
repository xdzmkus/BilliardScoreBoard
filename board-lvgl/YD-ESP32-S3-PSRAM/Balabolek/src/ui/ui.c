#include "ui.h"

uint32_t LV_EVENT_GET_COMP_CALLBACK;
uint32_t LV_EVENT_SET_COMP_CALLBACK;

ui_comp_cb_t ui_comp_get_callback(lv_obj_t* comp)
{
    ui_comp_cb_t info;
    lv_obj_send_event(comp, LV_EVENT_GET_COMP_CALLBACK, &info);
    return info;
}

void ui_comp_set_callback(lv_obj_t* comp, ui_comp_cb_t cb)
{
    ui_comp_cb_t info = cb;
    lv_obj_send_event(comp, LV_EVENT_SET_COMP_CALLBACK, &info);
}

void get_component_callback_event_cb(lv_event_t* e)
{
    ui_comp_cb_t* c = lv_event_get_user_data(e);
    ui_comp_cb_t* info = lv_event_get_param(e);
    *info = *c;
}

void set_component_callback_event_cb(lv_event_t* e)
{
    ui_comp_cb_t* c = lv_event_get_user_data(e);
    ui_comp_cb_t* info = lv_event_get_param(e);
    *c = *info;
}

void del_component_callback_event_cb(lv_event_t* e)
{
    ui_comp_cb_t* c = lv_event_get_user_data(e);
    lv_free(c);
}

uint32_t LV_EVENT_GET_COMP_CHILD;
uint32_t LV_EVENT_SET_COMP_CHILD;

typedef struct
{
    uint32_t child_idx;
    lv_obj_t* child;
} ui_comp_get_child_t;

lv_obj_t* ui_comp_get_child(lv_obj_t* comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_obj_send_event(comp, LV_EVENT_GET_COMP_CHILD, &info);
    return info.child;
}

void ui_comp_set_child(lv_obj_t* comp, uint32_t child_idx, lv_obj_t* obj)
{
    ui_comp_get_child_t info;
    info.child = obj;
    info.child_idx = child_idx;
    lv_obj_send_event(comp, LV_EVENT_SET_COMP_CHILD, &info);
}

void get_component_child_event_cb(lv_event_t* e)
{
    lv_obj_t** c = lv_event_get_user_data(e);
    ui_comp_get_child_t* info = lv_event_get_param(e);
    info->child = c[info->child_idx];
}

void set_component_child_event_cb(lv_event_t* e)
{
    lv_obj_t** c = lv_event_get_user_data(e);
    ui_comp_get_child_t* info = lv_event_get_param(e);
    c[info->child_idx] = info->child;
}

void del_component_child_event_cb(lv_event_t* e)
{
    lv_obj_t** c = lv_event_get_user_data(e);
    lv_free(c);
}

#define LV_KB_BTN(width) LV_BUTTONMATRIX_CTRL_POPOVER | width

const char* cyrillic_kb_map_lc[] = 
{   
    "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "ъ", LV_SYMBOL_BACKSPACE,"\n",
    "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", "ё", "-", "_","\n",
    LV_SYMBOL_UP, "я", "ч", "с", "м", "и", "т", "ь", "б", "ю", ".", ",", "@", "\n",
    "123", LV_SYMBOL_GLOBE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

const char* cyrillic_kb_map_uc[] = 
{
    "Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х", "Ъ", LV_SYMBOL_BACKSPACE, "\n",
    "Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э", "Ё", "-", "_","\n",
    LV_SYMBOL_DOWN, "Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю", ".", ",", "@", "\n",
    "123", LV_SYMBOL_GLOBE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

const lv_buttonmatrix_ctrl_t cyrillic_kb_ctrl_map[] =
{
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),  LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(2),
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),  LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KB_BTN(6), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2)
};

const char* latin_kb_map_lc[] =
{
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", LV_SYMBOL_BACKSPACE, "\n",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "-", "_","\n",
    LV_SYMBOL_UP, "z", "x", "c", "v", "b", "n", "m", ".", ",", "@", "\n",
    "123", LV_SYMBOL_GLOBE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

const char* latin_kb_map_uc[] =
{
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "-", "_", "\n",
    LV_SYMBOL_DOWN, "Z", "X", "C", "V", "B", "N", "M", ".", ",", "@", "\n",
    "123", LV_SYMBOL_GLOBE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

const lv_buttonmatrix_ctrl_t latin_kb_ctrl_map[] =
{
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(2),
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KB_BTN(6), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(1), LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2)
};

const char* special_kb_map[] =
{
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", LV_SYMBOL_BACKSPACE, "\n",
    "+", "&", "/", "*", "=", "%", "!", "?", "#", "<", ">", "\n",
    "\\", "$", "(", ")", "{", "}", "[", "]", ":", ";", "\"", "'", "\n",
    LV_SYMBOL_GLOBE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

const lv_buttonmatrix_ctrl_t special_kb_ctrl_map[] =
{
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(2),
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1), LV_KB_BTN(1),
    LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(2), LV_KB_BTN(6), LV_BTNMATRIX_CTRL_CHECKED | LV_KB_BTN(2), LV_KEYBOARD_CTRL_BUTTON_FLAGS | LV_KB_BTN(2)
};

const char* score_kb_map_num[] = 
{ 
    "1", "2", "3", "Отмена", "\n",
    "4", "5", "6", LV_SYMBOL_BACKSPACE, "\n",
    "7", "8", "9", "=", "\n",
    "+/-", "0", "Готово!", ""
};

const lv_buttonmatrix_ctrl_t score_kb_ctrl_num_map[] =
{
	1, 1, 1, LV_KEYBOARD_CTRL_BUTTON_FLAGS | 2,
	1, 1, 1, 2,
	1, 1, 1, 2,
	1, 1, LV_KEYBOARD_CTRL_BUTTON_FLAGS | 3
};

void ui_event_KeyboardButtons(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* obj = (lv_obj_t*)(lv_event_get_target(e));
	
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        const lv_keyboard_mode_t k_mode = lv_keyboard_get_mode(obj);

        const char* txt = lv_buttonmatrix_get_button_text(obj, lv_btnmatrix_get_selected_btn(obj));

        if (txt == NULL) return;

        if (strcmp(txt, LV_SYMBOL_DOWN) == 0)
        {
            if(k_mode == LV_KEYBOARD_MODE_USER_2)
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_1);
            else if(k_mode == LV_KEYBOARD_MODE_TEXT_UPPER)
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_TEXT_LOWER);
            
            return;
        }

        if (strcmp(txt, LV_SYMBOL_UP) == 0)
        {
            if(k_mode == LV_KEYBOARD_MODE_USER_1)
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_2);
            else if(k_mode == LV_KEYBOARD_MODE_TEXT_LOWER)
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_TEXT_UPPER);
            return;
        }

        if (strcmp(txt, LV_SYMBOL_GLOBE) == 0)
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

        if (strcmp(txt, "123") == 0)
        {
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_SPECIAL);
            return;
        }

        lv_keyboard_t* keyboard = (lv_keyboard_t*)obj;

        if(lv_strcmp(txt, LV_SYMBOL_OK) == 0)
        {
            lv_obj_send_event(obj, LV_EVENT_READY, NULL);
            if(keyboard->ta) lv_obj_send_event(keyboard->ta, LV_EVENT_READY, NULL);
            return;
        }

		/*Add the characters to the text area*/
        if (keyboard->ta == NULL) return;

        if(lv_strcmp(txt, LV_SYMBOL_LEFT) == 0)
        {
            lv_textarea_cursor_left(keyboard->ta);
        }
        else if(lv_strcmp(txt, LV_SYMBOL_RIGHT) == 0)
        {
            lv_textarea_cursor_right(keyboard->ta);
        }
        else if(lv_strcmp(txt, LV_SYMBOL_BACKSPACE) == 0)
        {
            lv_textarea_delete_char(keyboard->ta);
        }
        else
        {
            lv_textarea_add_text(keyboard->ta, txt);
        }
    }
}

void ui_event_ScoreKeyboardButtons(lv_event_t* e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	lv_obj_t* obj = (lv_obj_t*)(lv_event_get_target(e));

	lv_keyboard_t* keyboard = (lv_keyboard_t*)obj;

	if (keyboard->ta == NULL) return;

	if (event_code == LV_EVENT_VALUE_CHANGED)
	{
		uint16_t btn_id = lv_keyboard_get_selected_button(obj);

		if (btn_id == 3) // "Отмена"
		{
			lv_obj_send_event(obj, LV_EVENT_CANCEL, NULL);
			lv_obj_send_event(keyboard->ta, LV_EVENT_CANCEL, NULL);
			return;
		}
		
		if (btn_id == 14) // "Готово!"
		{
			lv_obj_send_event(obj, LV_EVENT_READY, NULL);
			lv_obj_send_event(keyboard->ta, LV_EVENT_READY, NULL);
			return;
		}

		/*Add the characters to the text area if set*/

		uint16_t cur = lv_textarea_get_cursor_pos(keyboard->ta);
		const char* ta_txt = lv_textarea_get_text(keyboard->ta);

		if (btn_id == 12) // "+/-"
		{
			char firstChar = ta_txt[0];

			if (firstChar == '-' || firstChar == '+' || firstChar == '=')
			{
				lv_textarea_set_cursor_pos(keyboard->ta, 1);
				lv_textarea_delete_char(keyboard->ta);
				lv_textarea_add_char(keyboard->ta, firstChar == '-' ? '+' : '-');
				lv_textarea_set_cursor_pos(keyboard->ta, cur);
			}
			else
			{
				lv_textarea_set_cursor_pos(keyboard->ta, 0);
				lv_textarea_add_char(keyboard->ta, '+');
				lv_textarea_set_cursor_pos(keyboard->ta, cur + 1);
			}
			return;
		}

		if (btn_id == 11) // "="
		{
			if (ta_txt[0] == '=') return;

			if (ta_txt[0] == '-' || ta_txt[0] == '+')
			{
				lv_textarea_set_cursor_pos(keyboard->ta, 1);
				lv_textarea_delete_char(keyboard->ta);
				lv_textarea_add_char(keyboard->ta, '=');
				lv_textarea_set_cursor_pos(keyboard->ta, cur);
			}
			else
			{
				lv_textarea_set_cursor_pos(keyboard->ta, 0);
				lv_textarea_add_char(keyboard->ta, '=');
				lv_textarea_set_cursor_pos(keyboard->ta, cur + 1);
			}
			return;
		}

		if (btn_id == 7) // "backspace"
		{
			if(cur != 1) lv_textarea_delete_char(keyboard->ta); // do not delete first char

			return;
		}

		if (cur == 0)
        {
            // insert "=" if textarea is empty
            lv_textarea_add_char(keyboard->ta, '=');
			lv_textarea_set_cursor_pos(keyboard->ta, 1);
        }

		const char* txt = lv_buttonmatrix_get_button_text(obj, btn_id);
		if (txt == NULL) return;

		lv_textarea_add_text(keyboard->ta, txt);
	}
}

