#pragma once

#include <Arduino.h>

#define CUSTOM_MALLOC(x) heap_caps_malloc(x, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT)

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#define SCREEN_ROTATION 1

#define LVGL_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10)

#define TFT_LED         27
#define TFT_LED_LEVEL   HIGH

#define TFT_MISO 12  // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC   2   // Data Command control pin
#define TFT_RST  -1  // Reset pin (could connect to RST pin)

#define TC_SDA  33
#define TC_SCL  32
#define TC_INT  21
#define TC_RST  25

#define SD_MISO 19
#define SD_MOSI 23
#define SD_SCLK 18
#define SD_SS 5

#define BCLK_PIN 22
#define DIN_PIN  26
#define LRC_PIN  21
//#define SD_PIN   38

#define SAY_LOLEK 1000
#define SAY_BOLEK 1001
#define SAY_BYE 1002
#define SAY_GAME 1003
#define SAY_FRAME 1004
#define SAY_MIN -255
#define SAY_MAX 255

#define SAY_HELLO SAY_LOLEK

typedef struct _BOARD_OPTIONS
{
	char sta_ssid[33];
	char sta_pass[33];
	char bot_channel[33];
	char mqtt_host[64];
	char mqtt_port[6];
	char mqtt_user[33];
	char mqtt_pass[33];
	char greeting[129];
	bool isAPEnabled;
	bool isWifiEnabled;
	bool isTelegaEnabled;
	bool isAudioEnabled;
	uint8_t audioVolume;
} BOARD_EEPROM_DATA;

extern BOARD_EEPROM_DATA boardEEPROMdata;

extern const char* const WLAN_HOSTNAME;
extern const char* const MQTT_TOPIC;
extern const char bot_token[];
extern const char* const AP_SITE;

// Load DigiCert Global Root CA ca_cert, which is used by EMQX Cloud Serverless Deployment
extern const char ca_cert[];

#include <Arduino_GFX_Library.h>

extern Arduino_GFX* gfx;

#include <CTouch_GT911.h>

extern GT911 ts;

#include <SPI.h>

extern SPIClass SDSPI;
