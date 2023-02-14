/*
 * appMain.cpp
 *
 *  Author: xdzmkus
 */

#include "appMain.h"

#include "main.h"

#include "../../Drivers/LCD/lcd.h"
#include "../../Drivers/Touch/touch.h"

#include "../../lvgl/lvgl.h"
#include "../ui/ui.h"

#include <stdio.h>
#include <algorithm>

#define DISP_HOR_RES 240
#define DISP_VER_RES 320

extern RTC_HandleTypeDef hrtc;
extern volatile bool timeChanged;

void lcd_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area,
		lv_color_t *color_p)
{
	/*The most simple case (but also the slowest) to put all pixels to the screen one-by-one
	 *`put_px` is just an example, it needs to be implemented by you.*/
//	int32_t x, y;
//	for (y = area->y1; y <= area->y2; y++)
//	{
//		for (x = area->x1; x <= area->x2; x++)
//		{
//			LCD_DrawPixel(x, y, color_p->full);
//			color_p++;
//		}8
//	}

	LCD_DrawRGBImage(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t*)color_p);

	/* IMPORTANT!!!
	 * Inform the graphics library that you are ready with the flushing*/
	lv_disp_flush_ready(disp_drv);
}

void touch_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
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
void resetTimer()
{
	RTC_TimeTypeDef sTime =
	{ 0 };

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

static void appInit()
{
	Touch_Init();

	if (LCD_Init() == LCD_ERROR)
	{
		/* Initialization Error */
		Error_Handler();
	}

	LCD_SetRotation(1);

	/* A variable to hold the drivers. Must be static or global. */
	static lv_disp_drv_t disp_drv;

	/* A static or global variable to store the buffers */
	static lv_disp_draw_buf_t disp_buf;

	/* Static or global buffer(s). The second buffer is optional */
	static lv_color_t buf_1[DISP_HOR_RES * 10];

	/* A variable to hold the input device */
	static lv_indev_drv_t indev_drv;

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
}

void appMain()
{
	lv_init();

	appInit();

	ui_init();

	/* Infinite loop */
	while (1)
	{
		if (timeChanged)
		{
			timeChanged = false;

			RTC_TimeTypeDef sTime;
			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

			char currentTime[9];
			sprintf(currentTime, "%d:%02u:%02u", sTime.Hours, sTime.Minutes, sTime.Seconds);
			lv_msg_send(MSG_TIME_CHANGED, currentTime);
		}

		lv_timer_handler();
	}
}

