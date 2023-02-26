/*
 * ui_interact.h
 *
 *  Created on: 25 февр. 2023 г.
 *      Author: xdzmk
 */

#ifndef INC_LVGL_UI_INTERACT_H_
#define INC_LVGL_UI_INTERACT_H_

#ifdef __cplusplus
extern "C" {
#endif

void lvgl_ui_init();

void lvgl_ui_handle();

void lvgl_ui_change_time(const char* newTime);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* INC_LVGL_UI_INTERACT_H_ */
