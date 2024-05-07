
/*
 Name:		Balabolek.ino
 Author:	xdzmkus
*/

#include "src/defs.h"
#include "src/SerialDebug.h"
#include "src/EEPROMHelper.h"
#include "src/TaskTouch.h"
#include "src/TaskAudio.h"
#include "src/TaskInteract.h"
#include "src/gui.h"

extern const unsigned char dk_image[] PROGMEM;

static uint8_t* disp_draw_buf1;

#include <ClockTimer.hpp>
static ArduLibs::MillisTimer waterMarkTimer(60000);

#if LV_USE_LOG != 0
static void lvgl_Serial_print( lv_log_level_t level, const char * buf )
{
    SerialDebug.log(static_cast<LOG_LEVEL>(level), buf);
}
#endif

/* Read the touchpad */
static void lcd_touchpad_read(lv_indev_t* indev_driver, lv_indev_data_t* data)
{
    data->state = touchpad_read(data->point.x, data->point.y) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

/* Display flushing */
static void lcd_disp_flush(lv_display_t* disp, const lv_area_t* area,  uint8_t* px_map)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)px_map, w, h);

    lv_disp_flush_ready(disp);
}

void setup_LVGL()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Setup LCD"));
    
    lv_init();

    /* register print function for debugging */
#if LV_USE_LOG != 0
    lv_log_register_print_cb( lvgl_Serial_print );
#endif

    disp_draw_buf1 = (uint8_t*)CUSTOM_MALLOC(LVGL_BUF_SIZE * (LV_COLOR_DEPTH / 8));

    if (!disp_draw_buf1)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, F("LVGL disp_draw_buf allocate failed!"));
        ESP.restart();
    }

    /*Initialize the display*/
    lv_display_t * disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(disp, lcd_disp_flush);
    lv_display_set_buffers(disp, disp_draw_buf1, NULL, LVGL_BUF_SIZE * (LV_COLOR_DEPTH / 8), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /*Initialize the (dummy) input device driver*/
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, lcd_touchpad_read);

	SerialDebug.log(LOG_LEVEL::INFO, F("Setup LCD done."));
}

void setup()
{
    SerialDebug.begin(115200);

#ifdef TFT_LED
	pinMode(TFT_LED, OUTPUT);
	digitalWrite(TFT_LED, TFT_LED_LEVEL);
#endif

    // Init Display
    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->draw16bitRGBBitmap(80, 0, (const uint16_t*)dk_image, 320, 320);

    delay(2000); // time to show "DK" Logo

 	SerialDebug.log(LOG_LEVEL::INFO, F("Setup board"));

    SerialDebug.log(LOG_LEVEL::DEBUG, String("Total heap: ") + ESP.getHeapSize());
    SerialDebug.log(LOG_LEVEL::DEBUG, String("Total PSRAM: ") + ESP.getPsramSize());

    SerialDebug.log(LOG_LEVEL::DEBUG, String("Free heap: ") + ESP.getFreeHeap());
    SerialDebug.log(LOG_LEVEL::DEBUG, String("Free PSRAM: ") + ESP.getFreePsram());

    loadEEPROMdata();

    setup_Touch(SCREEN_ROTATION);

    setup_LVGL();

    setup_Interact();

    setup_Audio();

    gui_mutex = xSemaphoreCreateMutex(); // Create the mutex

    if (gui_mutex == NULL)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, String(F("Cannot create Mutex")));

        ESP.restart();
    }

    gui_init();

	waterMarkTimer.start();

    SerialDebug.log(LOG_LEVEL::DEBUG, String("Free heap: ") + ESP.getFreeHeap());
    SerialDebug.log(LOG_LEVEL::DEBUG, String("Free PSRAM: ") + ESP.getFreePsram());

   	SerialDebug.log(LOG_LEVEL::INFO, F("Setup board done."));
}

void loop()
{
    // Try to take the mutex
    if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
    {
        static uint32_t last_tick = 0;
        uint32_t act_tick = millis();

        lv_tick_inc(act_tick - last_tick);

        last_tick = act_tick;

        lv_timer_handler(); /* let the GUI do its work */

        xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
    }

	if (waterMarkTimer.isReady())
	{
        SerialDebug.log(LOG_LEVEL::DEBUG, String("Free heap: ") + ESP.getFreeHeap());
        SerialDebug.log(LOG_LEVEL::DEBUG, String("Free PSRAM: ") + ESP.getFreePsram());
        SerialDebug.log(LOG_LEVEL::DEBUG, String("GUI Stack water mark: ") + uxTaskGetStackHighWaterMark(NULL));
    }

    vTaskDelay(5);
}

