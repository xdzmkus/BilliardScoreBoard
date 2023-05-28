﻿#include "gui.h"
#include "gui_components.h"
#include "gui_main.h"
#include "gui_settings.h"
#include "gui_lottery.h"
#include "gui_pool.h"
#include "gui_snooker.h"
#include "gui_balls.h"

#include "ui/ui.h"
#include "ui/ui_helpers.h"

void gui_init()
{
    lv_disp_t* dispp = lv_disp_get_default();
    lv_theme_t* theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
    LV_EVENT_SET_COMP_CHILD = lv_event_register_id();

    gui_main_init();

    gui_lottery_init();

    gui_pool_init();

    gui_snooker_init();

    gui_balls_init();

    gui_settings_init();
    
    lv_disp_load_scr(ui_ScreenMain);
}

