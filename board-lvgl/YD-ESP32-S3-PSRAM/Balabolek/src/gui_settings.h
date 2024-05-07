#ifndef _GUI_SETTINGS_H
#define _GUI_SETTINGS_H

#include "ui/ui.h"

// SCREEN: ui_ScreenSettings
extern lv_obj_t * ui_ScreenSettings;

// SCREEN: ui_ScreenRestore
extern lv_obj_t *ui_ScreenRestore;

void gui_settings_create();
void gui_restore_create();

#endif
