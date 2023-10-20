#include "gui.h"
#include "gui_components.h"
#include "gui_main.h"
#include "gui_settings.h"
#include "gui_pool.h"
#include "gui_snooker.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

SemaphoreHandle_t gui_mutex = NULL;

SNOOKER_ACTION historyActions[MAX_ACTIONS];		// list of actions

uint16_t numberActions = 0;						// number of executed actions

int16_t pool2Ply1Score = 0;
int16_t pool2Ply2Score = 0;
int16_t pool3Ply1Score = 0;
int16_t pool3Ply2Score = 0;
int16_t pool3Ply3Score = 0;

POOL_PLAYER_BREAK poolPlyBreak = LEFT;

POOL_PLAYER_COUNT poolPlyCount = TWO;

void gui_init()
{
    lv_disp_t* dispp = lv_disp_get_default();
    lv_theme_t* theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
    LV_EVENT_SET_COMP_CHILD = lv_event_register_id();

    gui_settings_create();  // screen always exists

    gui_main_create();      // screen always exists

    lv_disp_load_scr(ui_ScreenMain);
}

String gui_getState()
{
    String msg;

    const char delimiter[] = "~";

    msg += lv_label_get_text(ui_SLabelNamePly1);    // idx = 0
    msg += delimiter;

    msg += lv_label_get_text(ui_SLabelNamePly2);    // idx = 1
    msg += delimiter;

    msg += lv_label_get_text(ui_SLabelNamePly3);    // idx = 2
    msg += delimiter;

    msg += lv_textarea_get_text(ui_STextAreaHandicap1); // idx = 3
    msg += delimiter;

    msg += lv_textarea_get_text(ui_STextAreaHandicap2); // idx = 4
    msg += delimiter;
    
    msg += lv_obj_has_state(ui_SSwitch6Red, LV_STATE_CHECKED);  // idx = 5
    msg += delimiter;

    msg += lv_obj_has_state(ui_SSwitchControl, LV_STATE_CHECKED);   // idx = 6
    msg += delimiter;

    msg += pool2Ply1Score;  // idx = 7
    msg += delimiter;

    msg += pool2Ply2Score;  // idx = 8
    msg += delimiter;

    msg += pool3Ply1Score;  // idx = 9
    msg += delimiter;

    msg += pool3Ply2Score;  // idx = 10
    msg += delimiter;

    msg += pool3Ply3Score;  // idx = 11
    msg += delimiter;

    msg += poolPlyBreak;    // idx = 12
    msg += delimiter;

    msg += poolPlyCount;    // idx = 13
    msg += delimiter;

    if (numberActions > 0)
    {
        msg += "SNKR";  // idx = 14...
        msg += delimiter;

        for (uint8_t idx = 0; idx < numberActions; idx++)
        {
            msg += historyActions[idx];
            msg += delimiter;
        }
    }

    return msg;
}

void gui_restoreState(String& value, uint8_t idx)
{
    switch (idx)
    {
    case 0:
        lv_label_set_text(ui_SLabelNamePly1, value.c_str());
        break;
    case 1:
        lv_label_set_text(ui_SLabelNamePly2, value.c_str());
        break;
    case 2:
        lv_label_set_text(ui_SLabelNamePly3, value.c_str());
        break;
    case 3:
        lv_textarea_set_text(ui_STextAreaHandicap1, value.c_str());
        break;
    case 4:
        lv_textarea_set_text(ui_STextAreaHandicap2, value.c_str());
        break;
    case 5:
        _ui_state_modify(ui_SSwitch6Red, LV_STATE_CHECKED, value.toInt() ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        break;
    case 6:
        _ui_state_modify(ui_SSwitchControl, LV_STATE_CHECKED, value.toInt() ? _UI_MODIFY_STATE_ADD : _UI_MODIFY_STATE_REMOVE);
        break;
    case 7:
        pool2Ply1Score = value.toInt();
        break;
    case 8:
        pool2Ply2Score = value.toInt();
        break;
    case 9:
        pool3Ply1Score = value.toInt();
        break;
    case 10:
        pool3Ply2Score = value.toInt();
        break;
    case 11:
        pool3Ply3Score = value.toInt();
        break;
    case 12:
        poolPlyBreak = static_cast<POOL_PLAYER_BREAK>(value.toInt());
        break;
    case 13:
        poolPlyCount = static_cast<POOL_PLAYER_COUNT>(value.toInt());
        break;
    case 14:
        numberActions = 0;
        break;
    default:
        historyActions[numberActions++] = static_cast<SNOOKER_ACTION>(value.toInt());
        break;
    }
}
