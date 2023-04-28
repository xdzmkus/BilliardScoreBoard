//#define SERIAL_DEBUG
#include <SerialDebug.h>

extern const unsigned char dk_image[] PROGMEM;

#include <EEPROMHelper.h>

#define WIFI_SSID "GENKA"
#define WIFI_PASS "123456789"
#define BOT_TOKEN "bot_token"
#define CHANNEL_ID "@genka"
#define GREETING "Геннадий Дмитриевич, ну или Г Е Н К А  <>"

static char wifi_ssid[33] = WIFI_SSID;
static char wifi_pass[33] = WIFI_PASS;
static char bot_token[65] = BOT_TOKEN;
static char bot_channel[33] = CHANNEL_ID;
static char greeting[97] = GREETING;

#include "WiFi.h"

#define WLAN_HOSTNAME "GENKA"

#include "Insights.h"
const char insights_auth_key[] = "eyJhbG...pQzsQ";

#include <WiFiManager.h>
WiFiManager wm;

WiFiManagerParameter custom_wifi_ssid;
WiFiManagerParameter custom_wifi_pass;
WiFiManagerParameter custom_bot_token;
WiFiManagerParameter custom_bot_channel;

#define FB_NO_OTA
#include <FastBot.h>
FastBot bot;

#define SQW 5

#include <RTClib.h>

RTC_DS3231 rtc;

volatile bool rtc_tick = false;

#include <CTouch_GT911.h>

#define C_SDA  21
#define C_SCL  22
#define C_INT  16
#define C_RST  17

GT911 ts = GT911(C_SDA, C_SCL, C_INT, C_RST);

static Touch_Point lastTouch;
static bool point_updated = false;

volatile bool touched = false;

#include <Arduino_GFX_Library.h>

#define TFT_MISO 19  // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15  // Chip select control pin
#define TFT_DC   2   // Data Command control pin
#define TFT_RST  GFX_NOT_DEFINED // Reset pin (could connect to RST pin)

const uint8_t rotation = 1;

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus* bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, TFT_SCLK /* SCK */, TFT_MOSI /* MOSI */, TFT_MISO /* MISO */, VSPI /* spi_num */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX* gfx = new Arduino_ILI9488_18bit(bus, TFT_RST, rotation /* rotation */, false /* IPS */);

static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

#include <lvgl.h>

static lv_disp_draw_buf_t draw_buf;
static lv_color_t* disp_draw_buf;

#include "src/gui.h"

#if defined(ESP8266) || defined(ESP32)
IRAM_ATTR
#endif
void isr_rtc_tick()
{
    rtc_tick = true;
}

#if defined(ESP8266) || defined(ESP32)
IRAM_ATTR
#endif
void isr_On_Touched()
{
    touched = true; // The panel was touched, the interrupt was performed.
}

void on_1_PointTouched(const Touch_Point& tp)
{
    lastTouch = tp;
    point_updated = true;
}

/*Read the touchpad*/
void lcd_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
    if (point_updated)
    {
        point_updated = false;

        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = lastTouch.x;
        data->point.y = lastTouch.y;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
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

void setup_RTC()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC!");
        Serial.flush();

        return;
    }

    pinMode(SQW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(SQW), isr_rtc_tick, FALLING);

    // we don't need the 32K Pin, so disable it
    rtc.disable32K();

    rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
}

void setup_LCD()
{
    ts.init(isr_On_Touched);
    ts.setRotation(rotation);
    ts.setCallback_1_PointTouched(on_1_PointTouched);
    
    // Init Display
    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->draw16bitRGBBitmap(80, 0, (const uint16_t*)dk_image, 320, 320);

    lv_init();

#ifdef ESP32
    disp_draw_buf = (lv_color_t*)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
    disp_draw_buf = (lv_color_t*)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 10);
#endif
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

void setup_WiFi()
{
    SerialDebug::log(LOG_LEVEL::INFO, F("Setup Wi-Fi"));

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WLAN_HOSTNAME);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);

    if (wm.getWiFiIsSaved())
    {
        WiFi.begin(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
    }

    new (&custom_wifi_ssid) WiFiManagerParameter("ssid", "WiFi AP SSID", wifi_ssid, 32);
    new (&custom_wifi_pass) WiFiManagerParameter("pass", "WiFi AP Password", wifi_pass, 32, " maxlength=31 type='password'");
    new (&custom_bot_token) WiFiManagerParameter("token", "Telegram Token", bot_token, 64, " maxlength=63");
    new (&custom_bot_channel) WiFiManagerParameter("channel", "Telegram Channel", bot_channel, 32, " maxlength=31");

    wm.addParameter(&custom_wifi_ssid);
    wm.addParameter(&custom_wifi_pass);
    wm.addParameter(&custom_bot_token);
    wm.addParameter(&custom_bot_channel);

    wm.setSaveParamsCallback(saveEEPROMConfig);
    wm.setConfigPortalBlocking(false);
    wm.setDisableConfigPortal(false);
}

void setup()
{
    SerialDebug::begin(115200);

 //   initEEPROM(); // run only once to save initial values

    loadEEPROM();

    setup_RTC();

    setup_LCD();

    gui_init();

    setup_WiFi();

    bot.setToken(bot_token);
    bot.setChatID(bot_channel);

    delay(2000);
}

void loop()
{
    if (wm.getConfigPortalActive()) wm.process();

    if (rtc_tick)
    {
        if (gui_rtc_save == true)
        {
            rtc.adjust(DateTime(gui_date_year, gui_date_month, gui_date_day, gui_time_hours, gui_time_minutes));

            gui_rtc_save = false;
        }

        DateTime now = rtc.now();

        gui_date_day = now.day();
        gui_date_month = now.month();
        gui_date_year = now.year();

        gui_time_hours = now.hour();
        gui_time_minutes = now.minute();

        gui_update_date();

        rtc_tick = false;
    }


    if (touched)
    {
        touched = false;

        ts.process();
    }

    lv_timer_handler(); /* let the GUI do its work */
}

const char* getGreetingMsg()
{
    return greeting;
}

void startDiagnostic()
{
    Insights.begin(insights_auth_key);
}

void stopDiagnostic()
{
    Insights.end();
}

void startConfigPortal()
{
    if (!wm.getConfigPortalActive())
    {
        wm.startConfigPortal(wifi_ssid, wifi_pass);

        SerialDebug::log(LOG_LEVEL::INFO, F("Config Portal started."));
    }
}

void stopConfigPortal()
{
    if (wm.getConfigPortalActive())
    {
        wm.stopConfigPortal();

        SerialDebug::log(LOG_LEVEL::INFO, F("Config Portal stopped."));
    }
}

int32_t sendMessageToChannel(String& msg, int32_t msgId = -1)
{
    if (gui_get_telegram_send() && WiFi.status() == WL_CONNECTED)
    {
        if (msgId != -1)
        {
            bot.deleteMessage(msgId);
        }

        if (bot.sendMessage(msg))
        {
            SerialDebug::log(LOG_LEVEL::INFO, String(F("Sent\n")) + msg);

            return bot.lastBotMsg();
        }
        else
        {
            SerialDebug::log(LOG_LEVEL::INFO, String(F("Sending failure\n")) + msg);
        }
    }

    return -1;
}

void saveEEPROMGreeting(const char* msg)
{
    EEPROMHelper::writeEEPROM(160, 96, msg);     // 160-256

    EEPROMHelper::commit();
}

static void saveEEPROMConfig()
{
    SerialDebug::log(LOG_LEVEL::INFO, F("Configuration changed. Need to save config."));

    strcpy(wifi_ssid, custom_wifi_ssid.getValue());
    strcpy(wifi_pass, custom_wifi_pass.getValue());
    strcpy(bot_token, custom_bot_token.getValue());
    strcpy(bot_channel, custom_bot_channel.getValue());

    EEPROMHelper::writeEEPROM(0, 32, wifi_ssid);     // 0-32
    EEPROMHelper::writeEEPROM(32, 32, wifi_pass);    // 32-64
    EEPROMHelper::writeEEPROM(64, 64, bot_token);    // 64-128
    EEPROMHelper::writeEEPROM(128, 32, bot_channel); // 128-160

    EEPROMHelper::commit();
}

static void loadEEPROM()
{
    EEPROMHelper::begin(256);

    EEPROMHelper::readEEPROM(0, 32).toCharArray(wifi_ssid, 32);     // 0-32
    EEPROMHelper::readEEPROM(32, 32).toCharArray(wifi_pass, 32);    // 32-64
    EEPROMHelper::readEEPROM(64, 64).toCharArray(bot_token, 64);    // 64-128
    EEPROMHelper::readEEPROM(128, 32).toCharArray(bot_channel, 32); // 128-160
    EEPROMHelper::readEEPROM(160, 96).toCharArray(greeting, 96);    // 160-256
}

static void initEEPROM()
{
    EEPROMHelper::begin(256);
    EEPROMHelper::writeEEPROM(0, 32, WIFI_SSID);     // 0-32
    EEPROMHelper::writeEEPROM(32, 32, WIFI_PASS);    // 32-64
    EEPROMHelper::writeEEPROM(64, 64, BOT_TOKEN);    // 64-128
    EEPROMHelper::writeEEPROM(128, 32, CHANNEL_ID);  // 128-160
    EEPROMHelper::writeEEPROM(160, 96, GREETING);    // 160-256
    EEPROMHelper::commit();
}

