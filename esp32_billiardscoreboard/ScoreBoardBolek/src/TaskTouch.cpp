#include "TaskTouch.h"
#include "SerialDebug.h"

#include <CTouch_GT911.h>

#define C_SDA  21
#define C_SCL  22
#define C_INT  16
#define C_RST  17

GT911 ts = GT911(C_SDA, C_SCL, C_INT, C_RST);

static bool is_touch_detected = false;
static Touch_Point lastTouchPoint;

#if defined(ESP8266) || defined(ESP32)
IRAM_ATTR
#endif
static void isr_On_Touched()
{
    is_touch_detected = true; // The panel was touched, the interrupt was performed.
}

/* Save touch point */
static void touch_cb(const Touch_Point& tp)
{
    lastTouchPoint = tp;
}


/* Read the touchpad */
bool touchpad_read(int16_t& x, int16_t& y)
{
    bool isTouch = false;

    if (is_touch_detected)
    {
        is_touch_detected = false;

        ts.process();

        /*Set the coordinates*/
        x = lastTouchPoint.x;
        y = lastTouchPoint.y;

        isTouch = true;
    }

    return isTouch;
}

void setup_Touch(uint8_t rotation)
{
    SerialDebug.log(LOG_LEVEL::INFO, F("Setup Touch Task"));

    ts.init(isr_On_Touched);
    ts.setRotation(rotation);
    ts.setCallback_1_PointTouched(touch_cb);
}

