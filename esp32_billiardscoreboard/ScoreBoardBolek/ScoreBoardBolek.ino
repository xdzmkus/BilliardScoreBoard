extern const unsigned char dk_image[] PROGMEM;

#include <lvgl.h>

static lv_disp_draw_buf_t draw_buf;
static lv_color_t* disp_draw_buf;

#include <Arduino_GFX_Library.h>

#define TFT_MISO 19  // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5   // Chip select control pin
#define TFT_DC   4   // Data Command control pin
#define TFT_RST  GFX_NOT_DEFINED // Reset pin (could connect to RST pin)

static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

const uint8_t rotation = 3;

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus* bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, TFT_SCLK /* SCK */, TFT_MOSI /* MOSI */, TFT_MISO /* MISO */, VSPI /* spi_num */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX* gfx = new Arduino_ILI9488_18bit(bus, TFT_RST, rotation /* rotation */, false /* IPS */);

#include "src/SerialDebug.h"
#include "src/EEPROMHelper.h"
#include "src/TaskTouch.h"
#include "src/TaskAudio.h"
#include "src/TaskNetwork.h"
#include "src/gui.h"

SemaphoreHandle_t gui_mutex = NULL;
SemaphoreHandle_t mem_mutex = NULL;

/* Read the touchpad */
void lcd_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
    data->state = touchpad_read(data->point.x, data->point.y) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

/* Display flushing */
void lcd_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

void setup_LCD()
{
    // Init Display
    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->draw16bitRGBBitmap(80, 0, (const uint16_t*)dk_image, 320, 320);

    lv_init();

    disp_draw_buf = (lv_color_t*)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        ESP.restart();
    }

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = lcd_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.rotated = LV_DISP_ROT_NONE;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lcd_touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

void setup()
{
    SerialDebug.begin(115200);

    // initEEPROM();

    loadEEPROM();

    setup_Touch(rotation);

    setup_LCD();

    delay(2000); // time to show "DK" Logo

    mem_mutex = xSemaphoreCreateMutex(); // Create the mutex

    if (mem_mutex == NULL)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, String(F("Cannot create Mutex")));

        ESP.restart();
    }

    if (setup_SDCARD())
    {
        setup_Audio();
    }
    else
    {
        gui_disableAudio();
    }

    setup_Network();

    gui_mutex = xSemaphoreCreateMutex(); // Create the mutex

    if (gui_mutex == NULL)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, String(F("Cannot create Mutex")));

        ESP.restart();
    }

    gui_init();
}

void loop()
{
    // Try to take the mutex
    if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
    {
        lv_timer_handler(); /* let the GUI do its work */

        xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
    }

    vTaskDelay(5);
}

