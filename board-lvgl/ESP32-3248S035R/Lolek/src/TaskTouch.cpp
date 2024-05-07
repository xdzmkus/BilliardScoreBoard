#include "defs.h"
#include "TaskTouch.h"
#include "SerialDebug.h"

#include <ClockTimer.hpp>

static bool is_touch_detected = false;
static Touch_Point lastTouchPoint;

static SemaphoreHandle_t touch_mutex = NULL;

/* Save touch point */
static void touch_cb(const Touch_Point& tp)
{
    // Try to take the mutex and wait indefintly if needed
    if (xSemaphoreTake(touch_mutex, portMAX_DELAY) == pdTRUE)
    {
        // Mutex successfully taken
        lastTouchPoint = tp;
        is_touch_detected = true;
    }
    xSemaphoreGive(touch_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
}

static void handleTOUCH(void* pvParameters)
{
    ArduLibs::MillisTimer waterMarkTimer(60000);
    waterMarkTimer.start();

    const TickType_t xDelay = 20 / portTICK_PERIOD_MS;

    for (;;)
    {
        ts.process();

        if (waterMarkTimer.isReady())
            SerialDebug.log(LOG_LEVEL::INFO, String(F("TOUCH Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(xDelay);
    }
}


/* Read the touchpad */
bool touchpad_read(int32_t& x, int32_t& y)
{
    bool isTouch = false;

    // Try to take the mutex and wait 10 ticks if needed
    if (xSemaphoreTake(touch_mutex, 10) == pdTRUE)
    {
        if (is_touch_detected)
        {
            is_touch_detected = false;

            /*Set the coordinates*/
            x = lastTouchPoint.x;
            y = lastTouchPoint.y;

            isTouch = true;
        }

        xSemaphoreGive(touch_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
    }

    return isTouch;
}

void setup_Touch(uint8_t rotation)
{
    SerialDebug.log(LOG_LEVEL::INFO, F("Setup Touch Task"));

    ts.init();
    ts.setRotation(rotation);
    ts.setCallback_1_PointTouched(touch_cb);

    touch_mutex = xSemaphoreCreateMutex(); // Create the mutex

    if (touch_mutex == NULL)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, String(F("Cannot create Mutex")));

        ESP.restart();
    }

    xTaskCreatePinnedToCore(
        handleTOUCH
        , "Touch handler"
        , 1500  // Stack size
        , NULL  // Pass reference to a variable
        , tskIDLE_PRIORITY + 2    // Priority
        , NULL  // Task handle is not used here - simply pass NULL
        , 1 // Core on which the task will run
    );
}

