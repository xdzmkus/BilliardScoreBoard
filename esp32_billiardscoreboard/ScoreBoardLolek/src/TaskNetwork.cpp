﻿#include "TaskNetwork.h"
#include "SerialDebug.h"
#include "EEPROMHelper.h"
#include "gui.h"
#include "gui_main.h"

extern SemaphoreHandle_t gui_mutex;
extern SemaphoreHandle_t mem_mutex;

#define WLAN_HOSTNAME "LOLEK"
const char* const MQTT_TOPIC = "diamond/lolek/history";

#include <WiFi.h>
WiFiClient client;

#include <PubSubClient.h>
PubSubClient mqtt;

#define FB_NO_OTA
#include <FastBot.h>
FastBot bot;

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

#include <ClockTimer.hpp>
MillisTimer wifiTimer(300000); // 5 minutes

static SemaphoreHandle_t wm_mutex = NULL;

static QueueHandle_t scoreQueueHandle = NULL;
static const int scoreQueueElementSize = 2;

static volatile bool v_publishHistory = false;
static volatile bool v_waitingHistory = false;
static volatile bool v_subscribeHistory = false;

////////////// 

static void receiveMQTTmesssage(char* topic, uint8_t* payload, unsigned int length)
{
	SerialDebug.log(LOG_LEVEL::DEBUG, String(F("MQTT Message arrived to ")) + topic);

	uint8_t tockenIdx = 0;

	String payloadTocken;

	if (v_waitingHistory)
	{
		// Try to take the mutex
		if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
		{
			for (uint8_t i = 0; i < length; i++)
			{
				char payloadChar = payload[i];

				if (payloadChar == '~')
				{
					SerialDebug.log(LOG_LEVEL::DEBUG, payloadTocken);

					gui_restoreState(payloadTocken, tockenIdx);

					++tockenIdx;

					payloadTocken.clear();
				}
				else
				{
					payloadTocken.concat(payloadChar);
				}
			}

			xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
		}

		v_waitingHistory = false;
	}

	mqtt.unsubscribe(MQTT_TOPIC);
}

static void handleNET(void* pvParameters)
{
	MillisTimer waterMarkTimer(60000);
	waterMarkTimer.start();

	for (;;)
	{
		if (WiFi.isConnected())
		{
			wifiTimer.reset();

			if (!mqtt.connected())
			{
				mqtt.connect(WLAN_HOSTNAME, mqtt_user, mqtt_pass);
			}
			else
			{
				if (v_subscribeHistory)
				{
					mqtt.subscribe(MQTT_TOPIC);

					v_waitingHistory = true;

					v_subscribeHistory = false;

					SerialDebug.log(LOG_LEVEL::INFO, String(F("Sent medical request")));
				}

				if (v_publishHistory)
				{
					SerialDebug.log(LOG_LEVEL::INFO, String(F("Sending history...")));

					String history;

					// Try to take the mutex
					if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
					{
						history = gui_getState();

						xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
					}

					if (mqtt.beginPublish(MQTT_TOPIC, history.length(), true))
					{
						mqtt.print(history);

						if (mqtt.endPublish())
							SerialDebug.log(LOG_LEVEL::DEBUG, String(F("SUCCESS")));
						else
							SerialDebug.log(LOG_LEVEL::ERROR, String(F("FAILED")));
					}
					else
					{
						SerialDebug.log(LOG_LEVEL::ERROR, String(F("Sending history FAILED")));
					}

					v_publishHistory = false;
				}

				mqtt.loop();
			}

			scoreMessage_t message;

			if (isTelegram && xQueueReceive(scoreQueueHandle, &message, 0) == pdPASS && xSemaphoreTake(mem_mutex, portMAX_DELAY) == pdTRUE)
			{
				static int32_t lastBotMsgId = 0;

				uint8_t status;

				SerialDebug.log(LOG_LEVEL::DEBUG, message.line);

				switch (message.type)
				{
				case T_COMMAND:
					status = bot.sendCommand(message.line, bot_channel);
					if (status == 1)
						SerialDebug.log(LOG_LEVEL::INFO, String(F("Sent Telega Command")));
					else
						SerialDebug.log(LOG_LEVEL::ERROR, String(F("Send Telega Command failure: ")) + status);
					break;
				case T_POOL_MESSAGE:
					status = bot.sendMessage(message.line, bot_channel);
					if (status == 1)
						SerialDebug.log(LOG_LEVEL::INFO, String(F("Sent Telega POOL msg")));
					else
						SerialDebug.log(LOG_LEVEL::ERROR, String(F("Sending Telega POOL failure: ")) + status);
					break;
				case T_SNOOKER_MESSAGE_UPD:
					if (lastBotMsgId != 0)
					{
						status = bot.deleteMessage(lastBotMsgId, bot_channel);
						SerialDebug.log(LOG_LEVEL::INFO, String(F("Deleting msg: ")) + lastBotMsgId + " status " + status);
						lastBotMsgId = 0;
					}
					// do not break;
				case T_SNOOKER_MESSAGE_NEW:
					status = bot.sendMessage(message.line, bot_channel);
					if (status == 1)
					{
						lastBotMsgId = bot.lastBotMsg();

						SerialDebug.log(LOG_LEVEL::INFO, String(F("Sent msg: ")) + lastBotMsgId);
					}
					else
					{
						SerialDebug.log(LOG_LEVEL::ERROR, String(F("Sending failure: ")) + status);
					}
					break;
				default:
					break;
				}

				xSemaphoreGive(mem_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
			}
		}
		else
		{
			if (wifiTimer.isReady())
			{
				startWiFi();
			}
		}

		// Try to take the mutex and wait 10 ticks if needed
		if (xSemaphoreTake(wm_mutex, 10) == pdTRUE)
		{
			if (wm.getConfigPortalActive())
			{
				wm.process();
			}

			xSemaphoreGive(wm_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
		}

		vTaskDelay(1);

		if (waterMarkTimer.isReady())
			SerialDebug.log(LOG_LEVEL::INFO, String(F("NETWORK Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));
	}
}

static void saveParams()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Configuration changed. Need to save parameters."));

	strncpy(ap_ssid, custom_wifi_ssid.getValue(), 32);
	strncpy(ap_pass, custom_wifi_pass.getValue(), 32);
	strncpy(bot_token, custom_bot_token.getValue(), 64);
	strncpy(bot_channel, custom_bot_channel.getValue(), 32);
	strncpy(mqtt_host, custom_mqtt_host.getValue(), 64);
	strncpy(mqtt_port, custom_mqtt_port.getValue(), 5);
	strncpy(mqtt_user, custom_mqtt_user.getValue(), 32);
	strncpy(mqtt_pass, custom_mqtt_pass.getValue(), 32);

	saveEEPROMParams();
}

static void saveWifi()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Configuration changed. Need to save wifi."));

	strncpy(sta_ssid, wm.getWiFiSSID().c_str(), 32);
	strncpy(sta_pass, wm.getWiFiPass().c_str(), 32);

	saveEEPROMWifi();
}

///////////// 

void setup_Network()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Setup Network Task"));

	WiFi.mode(WIFI_STA);
	WiFi.setHostname(WLAN_HOSTNAME);
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.setTxPower(WIFI_POWER_19_5dBm);    // Set WiFi RF power output to highest level

	startWiFi();

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

	wm.setSaveParamsCallback(saveParams);
	wm.setSaveConfigCallback(saveWifi);

	wm.setConfigPortalBlocking(false);
	wm.setDisableConfigPortal(false);

	mqtt.setClient(client);
	mqtt.setKeepAlive(60);
	mqtt.setBufferSize(256);
	mqtt.setServer(mqtt_host, atoi(mqtt_port));
	mqtt.setCallback(receiveMQTTmesssage);

	bot.setToken(bot_token);
	bot.setChatID(bot_channel);

	wm_mutex = xSemaphoreCreateMutex(); // Create the mutex

	if (wm_mutex == NULL)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Cannot create Mutex")));

		ESP.restart();
	}

	scoreQueueHandle = xQueueCreate(scoreQueueElementSize, sizeof(scoreMessage_t));

	// Check if the queue was successfully created
	if (scoreQueueHandle == NULL)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Queue could not be created.")));

		ESP.restart();
	}

	xTaskCreatePinnedToCore(
		handleNET
		, "Network handler"
		, 10000 // Stack size
		, NULL  // Pass reference to a variable
		, 1     // Priority
		, NULL  // Task handle is not used here - simply pass NULL
		, 0 // Core on which the task will run
	);
}

bool isConfigPortalStarted()
{
	bool res = false;

	// Try to take the mutex
	if (xSemaphoreTake(wm_mutex, portMAX_DELAY) == pdTRUE)
	{
		res = wm.getConfigPortalActive();

		xSemaphoreGive(wm_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	return res;
}

void startConfigPortal()
{
	// Try to take the mutex
	if (xSemaphoreTake(wm_mutex, portMAX_DELAY) == pdTRUE)
	{
		if (!wm.getConfigPortalActive())
		{
			wm.startConfigPortal(ap_ssid, ap_pass);

			SerialDebug.log(LOG_LEVEL::INFO, F("Config Portal started."));
		}

		xSemaphoreGive(wm_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}
}

void stopConfigPortal()
{
	// Try to take the mutex
	if (xSemaphoreTake(wm_mutex, portMAX_DELAY) == pdTRUE)
	{
		if (wm.getConfigPortalActive())
		{
			wm.stopConfigPortal();

			SerialDebug.log(LOG_LEVEL::INFO, F("Config Portal stopped."));
		}

		xSemaphoreGive(wm_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}
}

bool isWifiConnected()
{
	return WiFi.isConnected();
}

void startWiFi()
{
	SerialDebug.log(LOG_LEVEL::DEBUG, "Start Wifi");

	WiFi.disconnect(true, true);

	SerialDebug.log(LOG_LEVEL::DEBUG, String("Connect to SSID: ") + sta_ssid + " with password: " + sta_pass);

	WiFi.begin(sta_ssid, sta_pass);

	wifiTimer.start();
}

void stopWiFi()
{
	SerialDebug.log(LOG_LEVEL::DEBUG, "Stop Wifi");

	WiFi.disconnect(true);

	wifiTimer.stop();
}

bool isWaitingHistory()
{
	return v_waitingHistory || v_subscribeHistory;
}

void subscribeHistory()
{
	v_subscribeHistory = true;
}

void revokeHistory()
{
	v_subscribeHistory = false;
	v_waitingHistory = false;
}

void publishCurrentState()
{
	v_publishHistory = true;
}

void sendTelegaMessage(telegramMsgType_t type, String msg)
{
	uint16_t msgSize = msg.length() > MAX_LINE_LENGTH ? MAX_LINE_LENGTH : msg.length();

	// Check if there is any free space in the queue
	if (isTelegram && msgSize > 0 && uxQueueSpacesAvailable(scoreQueueHandle) > 0)
	{
		scoreMessage_t message;

		message.type = type;

		strncpy(message.line, msg.c_str(), msgSize);
		message.line[msgSize] = '\0';

		// The line needs to be passed as pointer to void.
		// The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
		// When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
		int ret = xQueueSend(scoreQueueHandle, (void*)&message, 0);
		if (ret == pdTRUE)
		{
			// The message was successfully sent.
		}
		else if (ret == errQUEUE_FULL)
		{
			// Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
			//   write into the same queue it can fill-up between the test and actual send attempt
			SerialDebug.log(LOG_LEVEL::DEBUG, String(F("Unable to send data into the Queue")));
		}
	}
}
