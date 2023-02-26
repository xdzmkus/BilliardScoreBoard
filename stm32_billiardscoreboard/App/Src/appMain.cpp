/*
 * appMain.cpp
 *
 *  Author: xdzmkus
 */

#include "appMain.h"

#include "main.h"

#include "lvgl_ui_interact.h"

#include <stdio.h>
#include <algorithm>

extern RTC_HandleTypeDef hrtc;
extern volatile bool timeChanged;


void resetTimer()
{
	RTC_TimeTypeDef sTime =	{ 0 };

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

void appMain()
{
	lvgl_ui_init();

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
			lvgl_ui_change_time(currentTime);
		}

		lvgl_ui_handle();
	}
}

