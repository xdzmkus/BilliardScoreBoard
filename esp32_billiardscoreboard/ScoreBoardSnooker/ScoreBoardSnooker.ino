//#define INIT_EEPROM

//#define SERIAL_DEBUG
#include <SerialDebug.h>

extern const unsigned char dk_image[] PROGMEM;

#include <EEPROMHelper.h>

static char ap_ssid[33] = {};
static char ap_pass[33] = {};
static char bot_token[65] = {};
static char bot_channel[33] = {};
static char greeting[97] = {};
static char sta_ssid[33] = {};
static char sta_pass[33] = {};
static char mqtt_host[65] = {};
static char mqtt_port[6] = {};
static char mqtt_user[33] = {};
static char mqtt_pass[33] = {};

#include "WiFi.h"

#define WLAN_HOSTNAME "BOLEK"

#include <WiFiManager.h>
WiFiManager wm;

WiFiManagerParameter custom_wifi_ssid;
WiFiManagerParameter custom_wifi_pass;
WiFiManagerParameter custom_bot_token;
WiFiManagerParameter custom_bot_channel;
WiFiManagerParameter custom_mqtt_host;
WiFiManagerParameter custom_mqtt_port;
WiFiManagerParameter custom_mqtt_user;
WiFiManagerParameter custom_mqtt_pass;

WiFiClient client;

#include <PubSubClient.h>

PubSubClient mqtt;

const char* const MQTT_TOPIC = "bolek/status";

#define FB_NO_OTA
#include <FastBot.h>

#include <ClockTimer.hpp>
MillisTimer wifiTimer(300000); // 5 minutes

#include <RTClib.h>
#define SQW 2
RTC_DS3231 rtc;
volatile bool rtc_tick = false;

#include <CTouch_GT911.h>

#define C_SDA  21
#define C_SCL  22
#define C_INT  16
#define C_RST  17

GT911 ts = GT911(C_SDA, C_SCL, C_INT, C_RST);

static bool is_touch_detected = false;
static Touch_Point lastTouchPoint;

#include <Arduino_GFX_Library.h>

#define TFT_MISO 19  // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5   // Chip select control pin
#define TFT_DC   4   // Data Command control pin
#define TFT_RST  GFX_NOT_DEFINED // Reset pin (could connect to RST pin)

static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

const uint8_t rotation = 1;

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus* bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, TFT_SCLK /* SCK */, TFT_MOSI /* MOSI */, TFT_MISO /* MISO */, VSPI /* spi_num */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX* gfx = new Arduino_ILI9488_18bit(bus, TFT_RST, rotation /* rotation */, false /* IPS */);

#include <lvgl.h>

static lv_disp_draw_buf_t draw_buf;
static lv_color_t* disp_draw_buf;

#include "src/gui.h"
#include "src/gui_main.h"
#include "src/gui_pool.h"
#include "src/gui_snooker.h"

volatile uint8_t publishPoolScore = 0;      // 0 - don't publish; 1 - new message
volatile uint8_t publishSnookerScore = 0;   // 0 - don't publish; 1 - replace last message; 2 - new message
volatile bool publishPoll = false;
volatile bool publishHistory = false;
volatile bool subscribeHistory = false;
volatile bool waitingHistory = false;

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

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
    is_touch_detected = true; // The panel was touched, the interrupt was performed.
}

/* Save touch point */
void touch_cb(const Touch_Point& tp)
{
    lastTouchPoint = tp;
}

/*Read the touchpad*/
void lcd_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
    if (is_touch_detected)
    {
        is_touch_detected = false;

        ts.process();
        
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = lastTouchPoint.x;
        data->point.y = lastTouchPoint.y;
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

void receiveMQTTmesssage(char* topic, uint8_t* payload, unsigned int length)
{
    SerialDebug::log(LOG_LEVEL::DEBUG, String(F("MQTT Message arrived to ")) + topic);

    uint8_t tockenIdx = 0;

    String payloadTocken;

    if (waitingHistory)
    {
        for (uint8_t i = 0; i < length; i++)
        {
            char payloadChar = payload[i];

            if (payloadChar == '\n')
            {
                SerialDebug::log(LOG_LEVEL::DEBUG, payloadTocken);

                if (tockenIdx <= 9)
                {
                    gui_pool_restoreHistory(payloadTocken, tockenIdx);
                }
                else
                {
                    gui_snooker_restoreHistory(payloadTocken, tockenIdx);
                }
                ++tockenIdx;
                payloadTocken.clear();
            }
            else
            {
                payloadTocken.concat(payloadChar);
            }
        }

        waitingHistory = false;
    }

    mqtt.unsubscribe(MQTT_TOPIC);
}

void handleNET(void* pvParameters)
{
    const TickType_t xDelay = 3000 / portTICK_PERIOD_MS;

    FastBot bot(bot_token);

    mqtt.setClient(client);
    mqtt.setKeepAlive(60);
    mqtt.setBufferSize(256);
    mqtt.setServer(mqtt_host, atoi(mqtt_port));
    mqtt.setCallback(receiveMQTTmesssage);

    for (;;)
    {
        if (WiFi.isConnected())
        {
            wifiTimer.reset();

            if (!mqtt.connected())
            {
                mqtt.connect(WLAN_HOSTNAME, mqtt_user, mqtt_pass);
            }

            if (subscribeHistory && mqtt.connected())
            {
                mqtt.subscribe(MQTT_TOPIC);

                subscribeHistory = false;

                SerialDebug::log(LOG_LEVEL::DEBUG, String(F("Sent medical request")));
            }

            if (publishHistory && mqtt.connected())
            {
                String history = gui_pool_getHistory() + gui_snooker_getHistory();

                if (mqtt.beginPublish(MQTT_TOPIC, history.length(), true))
                {
                    mqtt.print(history);

                    if (mqtt.endPublish())
                        publishHistory = false;
                }

                SerialDebug::log(LOG_LEVEL::INFO, String(F("Sent history")));
            }

            mqtt.loop();

            if (gui_main_isTelegram())
            {
                if (publishPoolScore > 0)
                {
                    String scoreMsg = gui_pool_getScore();

                    SerialDebug::log(LOG_LEVEL::INFO, scoreMsg);

                    if (bot.sendMessage(scoreMsg, bot_channel))
                    {
                        publishPoolScore = 0;

                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sent!")));
                    }
                    else
                    {
                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sending failure")));
                    }
                }

                if (publishPoll)
                {
                    publishPoll = false;

                    String poll = F("/sendPoll?question=И кто же победит?");
                    poll += F("&options=[");
                    poll += gui_pool_getPollQuestion();
                    poll += F("]");

                    if (bot.sendCommand(poll, bot_channel))
                    {
                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sent Poll!")));
                    }
                    else
                    {
                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sending Poll failure")));
                    }
                }

                if (publishSnookerScore > 0)
                {
                    static int32_t lastSnookerMsgId = 0;

                    if (publishSnookerScore == 1 && lastSnookerMsgId != 0)
                    {
                        bot.deleteMessage(lastSnookerMsgId, bot_channel);
                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Deleted msg: \n")) + lastSnookerMsgId);
                    }

                    String scoreMsg = gui_snooker_getScore();
                    SerialDebug::log(LOG_LEVEL::INFO, scoreMsg);

                    if (bot.sendMessage(scoreMsg, bot_channel))
                    {
                        publishSnookerScore = 0;

                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sent!")));

                        lastSnookerMsgId = bot.lastBotMsg();
                    }
                    else
                    {
                        SerialDebug::log(LOG_LEVEL::INFO, String(F("Sending failure")));
                    }
                }
            }
        }
        else
        {
            if (wifiTimer.isReady())
            {
                startWiFi();
            }
        }
        
        //        SerialDebug::log(LOG_LEVEL::INFO, String(F("NET Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(xDelay);
    }
}

void setup_RTC()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC!");
        Serial.flush();

        return;
    }

    pinMode(SQW, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(SQW), isr_rtc_tick, FALLING);

    // we don't need the 32K Pin, so disable it
    rtc.disable32K();

    rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
}

void setup_LCD()
{
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
}

void setup_TOUCH()
{
    ts.init(isr_On_Touched);
    ts.setRotation(rotation);
    ts.setCallback_1_PointTouched(touch_cb);

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
    WiFi.onEvent(WiFiEvent);

    new (&custom_wifi_ssid) WiFiManagerParameter("ssid", "WiFi AP SSID", ap_ssid, 32);
    new (&custom_wifi_pass) WiFiManagerParameter("pass", "WiFi AP Password", ap_pass, 32, " maxlength=32 type='password'");
    new (&custom_bot_token) WiFiManagerParameter("token", "Telegram Token", bot_token, 64, " maxlength=64");
    new (&custom_bot_channel) WiFiManagerParameter("channel", "Telegram Channel", bot_channel, 32, " maxlength=32");
    new (&custom_mqtt_host) WiFiManagerParameter("mqtt_host", "MQTT hostname", mqtt_host, 64, " maxlength=64");
    new (&custom_mqtt_port) WiFiManagerParameter("mqtt_port", "MQTT port", mqtt_port, 5, " maxlength=5");
    new (&custom_mqtt_user) WiFiManagerParameter("mqtt_user", "MQTT user", mqtt_user, 32, " maxlength=32");
    new (&custom_mqtt_pass) WiFiManagerParameter("mqtt_pass", "MQTT pass", mqtt_pass, 32, " maxlength=32 type='password'");

    wm.addParameter(&custom_wifi_ssid);
    wm.addParameter(&custom_wifi_pass);
    wm.addParameter(&custom_bot_token);
    wm.addParameter(&custom_bot_channel);
    wm.addParameter(&custom_mqtt_host);
    wm.addParameter(&custom_mqtt_port);
    wm.addParameter(&custom_mqtt_user);
    wm.addParameter(&custom_mqtt_pass);

    wm.setSaveParamsCallback(saveEEPROMParams);
    wm.setSaveConfigCallback(saveEEPROMWifi);

    wm.setConfigPortalBlocking(false);
    wm.setDisableConfigPortal(false);
}

void setup()
{
    SerialDebug::begin(115200);

#ifdef INIT_EEPROM
    initEEPROM();
#endif

    loadEEPROM();

    setup_WiFi();

    setup_LCD();

    setup_TOUCH();

    setup_RTC();

    delay(2000);

    gui_init();

    xTaskCreatePinnedToCore(
        handleNET
        , "Network handler"
        , 10240 // Stack size
        , NULL  // Pass reference to a variable
        , 1     // Low priority
        , NULL  // Task handle is not used here - simply pass NULL
        , ARDUINO_RUNNING_CORE // Core on which the task will run
    );
}

void loop()
{
    if (wm.getConfigPortalActive())
    {
        wm.process();
    }

    lv_timer_handler(); /* let the GUI do its work */
}

void WiFiEvent(WiFiEvent_t event)
{
    String wifiEvent("[WiFi-event] : ");

    switch (event)
    {
    case ARDUINO_EVENT_WIFI_READY:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "WiFi interface ready");
        break;
    case ARDUINO_EVENT_WIFI_SCAN_DONE:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Completed scan for access points");
        break;
    case ARDUINO_EVENT_WIFI_STA_START:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "WiFi client started");
        break;
    case ARDUINO_EVENT_WIFI_STA_STOP:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "WiFi clients stopped");
        break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Connected to access point");
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Disconnected from WiFi access point");
        break;
    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Authentication mode of access point has changed");
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Obtained IP address: ");
        SerialDebug::log(LOG_LEVEL::DEBUG, WiFi.localIP().toString());
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "STA IPv6 is preferred");
        break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Lost IP address and IP address is reset to 0");
        break;
    case ARDUINO_EVENT_WIFI_AP_START:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "WiFi access point started");
        break;
    case ARDUINO_EVENT_WIFI_AP_STOP:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "WiFi access point  stopped");
        break;
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Client connected");
        break;
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Client disconnected");
        break;
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Assigned IP address to client");
        break;
    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "Received probe request");
        break;
    case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + "AP IPv6 is preferred");
        break;
    default:
        SerialDebug::log(LOG_LEVEL::DEBUG, wifiEvent + event);
        break;
    }
}

bool isWifiConnected()
{
    return WiFi.isConnected();
}

void startWiFi()
{
    SerialDebug::log(LOG_LEVEL::DEBUG, "Start Wifi");

    WiFi.disconnect(true);

    SerialDebug::log(LOG_LEVEL::DEBUG, String("Connect to SSID: ") + sta_ssid + " with password: " + sta_pass);

    WiFi.begin(sta_ssid, sta_pass);

    wifiTimer.start();
}

void stopWiFi()
{
    SerialDebug::log(LOG_LEVEL::DEBUG, "Stop Wifi");

    WiFi.disconnect(true);

    wifiTimer.stop();
}

bool isConfigPortalStarted()
{
    return wm.getConfigPortalActive();
}

void startConfigPortal()
{
    if (!wm.getConfigPortalActive())
    {
        wm.startConfigPortal(ap_ssid, ap_pass);

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

bool isWaitMedicalResponse()
{
    return waitingHistory;
}

void sendMedicalRequest()
{
    subscribeHistory = true;
    waitingHistory = true;
}

void revokeMedicalRequest()
{
    subscribeHistory = false;
    waitingHistory = false;
}

const char* getGreetingMsg()
{
    return greeting;
}

void saveEEPROMGreeting(const char* msg)
{
    EEPROMHelper::writeEEPROM(160, 96, msg);            // 160-255

    EEPROMHelper::commit();
}

static void saveEEPROMParams()
{
    SerialDebug::log(LOG_LEVEL::INFO, F("Configuration changed. Need to save parameters."));

    strncpy(ap_ssid, custom_wifi_ssid.getValue(), 32);
    strncpy(ap_pass, custom_wifi_pass.getValue(), 32);
    strncpy(bot_token, custom_bot_token.getValue(), 64);
    strncpy(bot_channel, custom_bot_channel.getValue(), 32);
    strncpy(mqtt_host, custom_mqtt_host.getValue(), 64);
    strncpy(mqtt_port, custom_mqtt_port.getValue(), 5);
    strncpy(mqtt_user, custom_mqtt_user.getValue(), 32);
    strncpy(mqtt_pass, custom_mqtt_pass.getValue(), 32);

    EEPROMHelper::writeEEPROM(0, 32, ap_ssid);          // 0-31
    EEPROMHelper::writeEEPROM(32, 32, ap_pass);         // 32-63
    EEPROMHelper::writeEEPROM(64, 64, bot_token);       // 64-127
    EEPROMHelper::writeEEPROM(128, 32, bot_channel);    // 128-159
    EEPROMHelper::writeEEPROM(320, 64, mqtt_host);      // 320-383
    EEPROMHelper::writeEEPROM(384, 5, mqtt_port);       // 384-388
    EEPROMHelper::writeEEPROM(389, 32, mqtt_user);      // 389-420
    EEPROMHelper::writeEEPROM(421, 32, mqtt_pass);      // 421-452

    EEPROMHelper::commit();
}

static void saveEEPROMWifi()
{
    SerialDebug::log(LOG_LEVEL::INFO, F("Configuration changed. Need to save wifi."));

    strncpy(sta_ssid, wm.getWiFiSSID().c_str(), 32);
    strncpy(sta_pass, wm.getWiFiPass().c_str(), 32);

    EEPROMHelper::writeEEPROM(256, 32, sta_ssid);       // 256-287
    EEPROMHelper::writeEEPROM(288, 32, sta_pass);       // 288-319

    EEPROMHelper::commit();
}

static void loadEEPROM()
{
    EEPROMHelper::begin(453);

    EEPROMHelper::readEEPROM(0, 32).toCharArray(ap_ssid, 32);       // 0-31
    EEPROMHelper::readEEPROM(32, 32).toCharArray(ap_pass, 32);      // 32-63
    EEPROMHelper::readEEPROM(64, 64).toCharArray(bot_token, 64);    // 64-127
    EEPROMHelper::readEEPROM(128, 32).toCharArray(bot_channel, 32); // 128-159
    EEPROMHelper::readEEPROM(160, 96).toCharArray(greeting, 96);    // 160-255
    EEPROMHelper::readEEPROM(256, 32).toCharArray(sta_ssid, 32);    // 256-287
    EEPROMHelper::readEEPROM(288, 32).toCharArray(sta_pass, 32);    // 288-319
    EEPROMHelper::readEEPROM(320, 64).toCharArray(mqtt_host, 64);   // 320-383
    EEPROMHelper::readEEPROM(384, 5).toCharArray(mqtt_port, 5);     // 384-388
    EEPROMHelper::readEEPROM(389, 32).toCharArray(mqtt_user, 32);   // 389-420
    EEPROMHelper::readEEPROM(421, 32).toCharArray(mqtt_pass, 32);   // 421-452

}

#ifdef INIT_EEPROM
static void initEEPROM()
{
    SerialDebug::log(LOG_LEVEL::INFO, F("EEPROM init"));

    EEPROMHelper::begin(453);

    EEPROMHelper::writeEEPROM(0, 32, "AP");                 // 0-31
    EEPROMHelper::writeEEPROM(32, 32, "APpass");            // 32-63
    EEPROMHelper::writeEEPROM(64, 64, "bot:token");         // 64-127
    EEPROMHelper::writeEEPROM(128, 32, "@channel");         // 128-159
    EEPROMHelper::writeEEPROM(160, 96, "https://t.me/channel"); // 160-255
    EEPROMHelper::writeEEPROM(256, 32, "SSID");             // 256-287
    EEPROMHelper::writeEEPROM(288, 32, "SSIDpass");         // 288-319
    EEPROMHelper::writeEEPROM(320, 64, "mqtt");             // 320-383
    EEPROMHelper::writeEEPROM(384, 5, "1883");              // 384-388
    EEPROMHelper::writeEEPROM(389, 32, "user");             // 389-420
    EEPROMHelper::writeEEPROM(421, 32, "pass");             // 421-452

    EEPROMHelper::commit();
}
#endif // INIT_EEPROM

