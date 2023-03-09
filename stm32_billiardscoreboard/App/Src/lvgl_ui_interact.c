/*
 * ui_interact.c
 *
 *  Created on: 26 февр. 2023 г.
 *      Author: xdzmk
 */

#include "lvgl_ui_interact.h"
#include "appMain.h"
#include "main.h"

#include "../../Drivers/LCD/lcd.h"
#include "../../Drivers/Touch/touch.h"

#include "../../lvgl/lvgl.h"
#include "../ui/ui.h"

#include <stdlib.h>

#define DISP_HOR_RES 240
#define DISP_VER_RES 320

#define MSG_TIME_CHANGED 100
#define MSG_SWITCH_CHANGED 101

/* A variable to hold the drivers. Must be static or global. */
static lv_disp_drv_t disp_drv;

/* A static or global variable to store the buffers */
static lv_disp_draw_buf_t disp_buf;

/* Static or global buffer(s). The second buffer is optional */
static lv_color_t buf_1[DISP_HOR_RES * 10];

/* A variable to hold the input device */
static lv_indev_drv_t indev_drv;

static int16_t ply1_score_value;
static int16_t ply2_score_value;
static int16_t ply3_score_value;
static int16_t ply4_score_value;
static int16_t ply5_score_value;

static void lcd_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area,
		lv_color_t *color_p)
{
	LCD_DrawRGBImage(area->x1, area->y1, area->x2 - area->x1 + 1,
			area->y2 - area->y1 + 1, (uint16_t*) color_p);

	/* IMPORTANT!!!
	 * Inform the graphics library that you are ready with the flushing*/
	lv_disp_flush_ready(disp_drv);
}

static void touch_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
	uint16_t x, y;

	if (Touch_GetPoint(&x, &y))
	{
		data->point.x = x;
		data->point.y = y;
		data->state = LV_INDEV_STATE_PRESSED;
	}
	else
	{
		data->state = LV_INDEV_STATE_RELEASED;
	}
}

static void time_event_cb(lv_event_t *e)
{
	lv_obj_t *label = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		lv_msg_t *m = lv_event_get_msg(e);
		lv_label_set_text(label, lv_msg_get_payload(m));
	}
	if (code == LV_EVENT_LONG_PRESSED)
	{
		resetTimer();

		lv_msg_send(MSG_TIME_CHANGED, "0:00:00");

		ply1_score_value = 0;
		lv_msg_update_value(&ply1_score_value);
		ply2_score_value = 0;
		lv_msg_update_value(&ply2_score_value);
		ply3_score_value = 0;
		lv_msg_update_value(&ply3_score_value);
		ply4_score_value = 0;
		lv_msg_update_value(&ply4_score_value);
		ply5_score_value = 0;
		lv_msg_update_value(&ply5_score_value);

		lv_obj_clear_state(ui_ball1, LV_STATE_CHECKED);
		lv_obj_clear_state(ui_ball2, LV_STATE_CHECKED);
		lv_obj_clear_state(ui_ball3, LV_STATE_CHECKED);
		lv_obj_clear_state(ui_ball4, LV_STATE_CHECKED);
		lv_obj_clear_state(ui_ball5, LV_STATE_CHECKED);
		lv_obj_clear_state(ui_ball6, LV_STATE_CHECKED);

		lv_label_set_text(ui_LabelRandom, "");
	}
}

static void label_event_cb(lv_event_t *e)
{
	lv_obj_t *label = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		if (label == ui_Label1P)
		{
			++ply1_score_value;
			lv_msg_update_value(&ply1_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label1M)
		{
			--ply1_score_value;
			lv_msg_update_value(&ply1_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label2P)
		{
			++ply2_score_value;
			lv_msg_update_value(&ply2_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label2M)
		{
			--ply2_score_value;
			lv_msg_update_value(&ply2_score_value);
			lv_msg_send(MSG_SWITCH_CHANGED, NULL);
		}
		else if (label == ui_Label3P)
		{
			++ply3_score_value;
			lv_msg_update_value(&ply3_score_value);
		}
		else if (label == ui_Label3M)
		{
			--ply3_score_value;
			lv_msg_update_value(&ply3_score_value);
		}
		else if (label == ui_Label4P)
		{
			++ply4_score_value;
			lv_msg_update_value(&ply4_score_value);
		}
		else if (label == ui_Label4M)
		{
			--ply4_score_value;
			lv_msg_update_value(&ply4_score_value);
		}
		else if (label == ui_Label5P)
		{
			++ply5_score_value;
			lv_msg_update_value(&ply5_score_value);
		}
		else if (label == ui_Label5M)
		{
			--ply5_score_value;
			lv_msg_update_value(&ply5_score_value);
		}
	}
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		lv_msg_t *m = lv_event_get_msg(e);
		const int16_t *v = lv_msg_get_payload(m);
		lv_label_set_text_fmt(label, "%d", *v);
	}
}

static void switch_event_cb(lv_event_t *e)
{
	lv_obj_t *sw = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_MSG_RECEIVED)
	{
		if (lv_obj_has_state(sw, LV_STATE_CHECKED))
			lv_obj_clear_state(sw, LV_STATE_CHECKED);
		else
			lv_obj_add_state(sw, LV_STATE_CHECKED);

		lv_obj_invalidate(sw);
	}
}

static void msg_init()
{
	lv_obj_add_event_cb(ui_Time, time_event_cb, LV_EVENT_ALL, NULL);
	lv_msg_subscribe_obj(MSG_TIME_CHANGED, ui_Time, NULL);

	lv_obj_add_event_cb(ui_Switch, switch_event_cb, LV_EVENT_MSG_RECEIVED,
			NULL);
	lv_msg_subscribe_obj(MSG_SWITCH_CHANGED, ui_Switch, NULL);

	lv_obj_add_event_cb(ui_Label1, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply1_score_value, ui_Label1, NULL);

	lv_obj_add_event_cb(ui_Label2, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply2_score_value, ui_Label2, NULL);

	lv_obj_add_event_cb(ui_Label3, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply3_score_value, ui_Label3, NULL);

	lv_obj_add_event_cb(ui_Label4, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply4_score_value, ui_Label4, NULL);

	lv_obj_add_event_cb(ui_Label5, label_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
	lv_msg_subscribe_obj((lv_msg_id_t) &ply5_score_value, ui_Label5, NULL);

	lv_obj_add_event_cb(ui_Label1P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label1M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label2P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label2M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label3P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label3M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label4P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label4M, label_event_cb, LV_EVENT_ALL, NULL);

	lv_obj_add_event_cb(ui_Label5P, label_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui_Label5M, label_event_cb, LV_EVENT_ALL, NULL);
}

void handleRandomBall(lv_event_t *e)
{
	lv_obj_t *target = lv_event_get_target(e);

	if (target == ui_PanelRand)
	{
		srand(HAL_GetTick());

		uint8_t rBall = 0;

		uint8_t x;
		for (x = 0; x < 100; ++x)
		{
			rBall = rand() % 6;

			if (rBall == 0 && !lv_obj_has_state(ui_ball1, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball1, LV_STATE_CHECKED);
				break;
			}
			if (rBall == 1 && !lv_obj_has_state(ui_ball2, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball2, LV_STATE_CHECKED);
				break;
			}
			if (rBall == 2 && !lv_obj_has_state(ui_ball3, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball3, LV_STATE_CHECKED);
				break;
			}
			if (rBall == 3 && !lv_obj_has_state(ui_ball4, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball4, LV_STATE_CHECKED);
				break;
			}
			if (rBall == 4 && !lv_obj_has_state(ui_ball5, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball5, LV_STATE_CHECKED);
				break;
			}
			if (rBall == 5 && !lv_obj_has_state(ui_ball6, LV_STATE_CHECKED))
			{
				lv_obj_add_state(ui_ball6, LV_STATE_CHECKED);
				break;
			}
		}

		if (x == 100)
		{
			lv_label_set_text(ui_LabelRandom, "");

			return;
		}

		lv_label_set_text_fmt(ui_LabelRandom, "%1d", rBall + 1);
	}
	else
	{
		lv_label_set_text(ui_LabelRandom, "");
	}
}

void lvgl_ui_init()
{
	Touch_Init();

	LCD_Init();

	LCD_SetRotation(1);

	lv_init();

	/* Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, DISP_HOR_RES * 10);

	lv_disp_drv_init(&disp_drv); /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
	disp_drv.flush_cb = lcd_flush_cb; /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = DISP_HOR_RES; /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = DISP_VER_RES; /*Set the vertical resolution in pixels*/
	disp_drv.rotated = LV_DISP_ROT_90;

	lv_disp_drv_register(&disp_drv); /*Register the driver in LVGL*/

	/* Register an input device */
	lv_indev_drv_init(&indev_drv); /*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touchpad or mouse*/
	indev_drv.read_cb = touch_input_read; /*Pointer callback to report the current state of an input device*/

	lv_indev_drv_register(&indev_drv); /*Register the driver in LVGL*/

	ui_init();

	msg_init();
}

void lvgl_ui_handle()
{
	lv_timer_handler();
}

void lvgl_ui_change_time(const char *newTime)
{
	lv_msg_send(MSG_TIME_CHANGED, newTime);
}

