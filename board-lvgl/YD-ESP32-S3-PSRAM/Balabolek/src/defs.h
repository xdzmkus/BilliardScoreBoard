#pragma once

#include <Arduino.h>

#define CUSTOM_MALLOC(x) ps_malloc(x)

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#define SCREEN_ROTATION 3

#define LVGL_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

//#define TFT_LED         27
//#define TFT_LED_LEVEL   HIGH

#define TFT_MISO 13  // (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_CS   10  // Chip select control pin
#define TFT_DC   14  // Data Command control pin
#define TFT_RST  -1  // Reset pin (connect to RST pin)

#define TC_SDA  8
#define TC_SCL  9
#define TC_INT  18
#define TC_RST  17

#define SD_MISO 41
#define SD_MOSI 40
#define SD_SCLK 39
#define SD_SS   42

#define BCLK_PIN 2
#define DIN_PIN  1
#define LRC_PIN  47
#define SD_PIN   38

#define SAY_LOLEK 1000
#define SAY_BOLEK 1001
#define SAY_BALABOLEK 1002
#define SAY_GAME 1003
#define SAY_FRAME 1004
#define SAY_MIN -255
#define SAY_MAX 255

#define SAY_HELLO SAY_BALABOLEK

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
