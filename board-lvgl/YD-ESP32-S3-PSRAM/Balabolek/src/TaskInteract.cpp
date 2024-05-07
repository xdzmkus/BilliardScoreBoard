#include "TaskInteract.h"
#include "SerialDebug.h"
#include "EEPROMHelper.h"
#include "gui.h"
#include "defs.h"


#include <WiFiClientSecure.h>
static WiFiClientSecure wifiClient;

#include <PubSubClient.h>
static PubSubClient mqttClient;

#include <TelegaBot.hpp>
static int32_t lastBotMsgId = 0;

#include <ClockTimer.hpp>
static ArduLibs::MillisTimer wifiTimer(180000);	// 3 minutes
static ArduLibs::MillisTimer mqttTimer(10000);	// 10 sec

static QueueHandle_t interactQueueHandle = NULL;
static const uint8_t interactQueueElementSize = 8;

static volatile bool v_wifiStarted = false;
static volatile bool v_wifiConnected = false;
static volatile bool v_waitingHistory = false;

static void connectSSID()
{
	char ssid[sizeof(boardEEPROMdata.sta_ssid)];
	char pass[sizeof(boardEEPROMdata.sta_pass)];

	// Try to take the mutex
	if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
	{
		strcpy(ssid, boardEEPROMdata.sta_ssid);
		strcpy(pass, boardEEPROMdata.sta_pass);

		xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	SerialDebug.log(LOG_LEVEL::DEBUG, String("Connect to SSID: ") + ssid + " with password: " + pass);
				
	WiFi.disconnect(true, true);

	WiFi.begin(ssid, pass);

	configTime(3 * 3600, 0, "pool.ntp.org"); // get UTC time via NTP
}

static void receiveMQTTmesssage(char* topic, uint8_t* payload, unsigned int length)
{
	SerialDebug.log(LOG_LEVEL::DEBUG, String(F("MQTT Message arrived to ")) + topic);

	if(strcmp(topic, MQTT_TOPIC) != 0) return;

	if (v_waitingHistory)
	{
		char* state = static_cast<char*>(CUSTOM_MALLOC(length + 1));
		memcpy(state, payload, length);
		state[length] = '\0';

		SerialDebug.log(LOG_LEVEL::DEBUG, state);

		// Try to take the mutex
		if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
		{
			gui_restoreCurrentState(state);

			xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
		}

		free(state);

		v_waitingHistory = false;
	}

	mqttClient.unsubscribe(MQTT_TOPIC);
}

static void publishMQTTmesssage(interactMessageBody_t &mBody)
{
	if(mBody.msg == NULL) return;

	if (mqttClient.connected())
	{
		SerialDebug.log(LOG_LEVEL::INFO, String(F("Send mqtt message...")));

		SerialDebug.log(LOG_LEVEL::DEBUG, mBody.msg);

		if (mqttClient.beginPublish(MQTT_TOPIC, strlen(mBody.msg), true))
		{
			mqttClient.print(mBody.msg);

			if (mqttClient.endPublish())
			{
				SerialDebug.log(LOG_LEVEL::DEBUG, String(F("SUCCESS")));
			}
			else
			{
				SerialDebug.log(LOG_LEVEL::ERROR, String(F("FAILED")));
			}
		}
		else
		{
			SerialDebug.log(LOG_LEVEL::ERROR, String(F("Send mqtt FAILED")));
		}
	}
}

static void subscribeMQTT()
{
	if(mqttClient.connected())
	{
		v_waitingHistory = mqttClient.subscribe(MQTT_TOPIC);

		if(v_waitingHistory)
		{
			SerialDebug.log(LOG_LEVEL::INFO, String(F("Subscibed to MQTT.")));
		}
		else
		{
			SerialDebug.log(LOG_LEVEL::ERROR, String(F("Subscibe to MQTT FAILED.")));
		}
	}
}

static void unsubscribeMQTT()
{
	if(mqttClient.connected())
	{
		v_waitingHistory = false;
				
		if(mqttClient.unsubscribe(MQTT_TOPIC))
		{	
			SerialDebug.log(LOG_LEVEL::INFO, String(F("UnSubscibed from MQTT.")));
		}
		else
		{	
			SerialDebug.log(LOG_LEVEL::ERROR, String(F("UnSubscibe from MQTT FAILED.")));
		}
	}
}

static void telegaPoll(interactMessageBody_t &mBody)
{
	if (!WiFi.isConnected()) return;

	char channel[sizeof(boardEEPROMdata.bot_channel)];

	// Try to take the mutex
	if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
	{
		strcpy(channel, boardEEPROMdata.bot_channel);

		xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	WiFiClientSecure telegaClient;
	ArduLibs::TelegaBot bot(bot_token, telegaClient);

	const char* options[3] = {mBody.opt1, mBody.opt2, mBody.opt3};

	if (bot.sendPoll(channel, mBody.msg, options, mBody.opt3 == NULL ? 2 : 3))
	{
		SerialDebug.log(LOG_LEVEL::INFO, String(F("Telega Poll sent.")));
	}
	else
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Telega Poll sending failure!")));
	}
}

static void telegaNewMsg(interactMessageBody_t &mBody)
{
	if (!WiFi.isConnected()) return;

	char channel[sizeof(boardEEPROMdata.bot_channel)];

	// Try to take the mutex
	if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
	{
		strcpy(channel, boardEEPROMdata.bot_channel);

		xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	WiFiClientSecure telegaClient;
	ArduLibs::TelegaBot bot(bot_token, telegaClient);

	if (bot.sendMessage(channel, mBody.msg))
	{
		lastBotMsgId = 0;

		SerialDebug.log(LOG_LEVEL::INFO, String(F("Telega Message sent.")));
	}
	else
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Telega Message sending failure!")));
	}
}

static void telegaUpdateMsg(interactMessageBody_t &mBody)
{
	if (!WiFi.isConnected()) return;

	char channel[sizeof(boardEEPROMdata.bot_channel)];

	// Try to take the mutex
	if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
	{
		strcpy(channel, boardEEPROMdata.bot_channel);

		xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	WiFiClientSecure telegaClient;
	ArduLibs::TelegaBot bot(bot_token, telegaClient);

	if (lastBotMsgId > 0)
	{
		if (bot.editMessage(channel, lastBotMsgId, mBody.msg))
		{
			lastBotMsgId = bot.getMsgID();

			SerialDebug.log(LOG_LEVEL::INFO, String(F("Telega Message edited.")));
		}
		else
		{
			SerialDebug.log(LOG_LEVEL::ERROR, String(F("Telega edit Message failure!")));
		}
	}
	else
	{
		if (bot.sendMessage(channel, mBody.msg))
		{
			lastBotMsgId = bot.getMsgID();

			SerialDebug.log(LOG_LEVEL::INFO, String(F("Telega Message sent.")));
		}
		else
		{
			SerialDebug.log(LOG_LEVEL::ERROR, String(F("Telega Message sending failure!")));
		}
	}
}

static void processWiFi()
{
	if(v_wifiStarted)
	{
		// start wifi if it's not yet started
		if(!wifiTimer.isActive())
		{
			connectSSID();

			wifiTimer.start();
			mqttTimer.start();
		}

		if (!WiFi.isConnected())
		{
			// reconnect to wifi if it is not connected a long time
			if (wifiTimer.isReady())
			{
				connectSSID();
			}
		}
	}
	else
	{
		// disconnect wifi if it's still connected
		if(wifiTimer.isActive())
		{
			WiFi.disconnect(true, true);

			wifiTimer.stop();
			mqttTimer.stop();
		}
	}

	// update wifi connection status
	v_wifiConnected = WiFi.isConnected();
}

static void processMQTT()
{
	if (!WiFi.isConnected()) return;

	// connect to mqtt
	if (!mqttClient.connected())
	{
		if (mqttTimer.isReady())
		{
			long port;
			char host[sizeof(boardEEPROMdata.mqtt_host)];
			char user[sizeof(boardEEPROMdata.mqtt_user)];
			char pass[sizeof(boardEEPROMdata.mqtt_pass)];

			// Try to take the mutex
			if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
			{
				port = atoi(boardEEPROMdata.mqtt_port);
				strcpy(host, boardEEPROMdata.mqtt_host);
				strcpy(user, boardEEPROMdata.mqtt_user);
				strcpy(pass, boardEEPROMdata.mqtt_pass);

				xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
			}

			if (port == 0) port = 1883;
			mqttClient.setServer(host, port);

			String clientId = String(WLAN_HOSTNAME) + "-" + String(random(0xffff), HEX);

			SerialDebug.log(LOG_LEVEL::INFO, String(clientId) + F(" connecting to MQTT..."));

			if (mqttClient.connect(clientId.c_str(), user, pass))
			{
				SerialDebug.log(LOG_LEVEL::DEBUG, String(F("SUCCESS")));
			}
			else
			{
				SerialDebug.log(LOG_LEVEL::ERROR, String(F("FAILED")));
			}
		}
	}
	else
	{	
		mqttClient.loop();
	}
}

static void processInteractMessage(interactMessage_t &message)
{
	switch (message.type)
	{
	case I_WIFI_ON:
		v_wifiStarted = true;
		break;
	case I_WIFI_OFF:
		v_wifiStarted = false;
		break;
	case I_MQTT_PUB:
		publishMQTTmesssage(message.body);
		break;
	case I_MQTT_SUB:
		subscribeMQTT();
		break;
	case I_MQTT_UNSUB:
		unsubscribeMQTT();
		break;
	case I_TELEGA_POLL:
		telegaPoll(message.body);
		break;
	case I_TELEGA_MSG_NEW:
		telegaNewMsg(message.body);
		break;
	case I_TELEGA_MSG_UPD:
		telegaUpdateMsg(message.body);
		break;
	default:
		break;
	}
}

static void freeInteractMessage(interactMessage_t &message)
{
	free(message.body.msg);
	free(message.body.opt1);
	free(message.body.opt2);
	free(message.body.opt3);
}

static void handleNetwork(void* pvParameters)
{
	ArduLibs::MillisTimer waterMarkTimer(60000); // 60 sec
	waterMarkTimer.start();
	
	for (;;)
	{
		processWiFi();

		processMQTT();

		interactMessage_t message;
		
		// receive intercact message
		if (xQueueReceive(interactQueueHandle, &message, 0) == pdPASS)
		{
			SerialDebug.log(LOG_LEVEL::INFO, String(F("Received Interact Message Type: ")) + message.type);

			processInteractMessage(message);

			freeInteractMessage(message);
		}

		if (waterMarkTimer.isReady())
		{
			SerialDebug.log(LOG_LEVEL::INFO, String(F("NETWORK Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));
		}

		vTaskDelay(1);
	}
}


void setup_Interact()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Setup Network."));

	WiFi.mode(WIFI_STA);
	WiFi.setHostname(WLAN_HOSTNAME);
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.setTxPower(WIFI_POWER_19_5dBm);    // Set WiFi RF power output to highest level
	WiFi.setSleep(false);
	
	wifiClient.setCACert(ca_cert);
	mqttClient.setClient(wifiClient);
	mqttClient.setKeepAlive(60);
	mqttClient.setBufferSize(256);
	mqttClient.setCallback(receiveMQTTmesssage);
	
	interactQueueHandle = xQueueCreate(interactQueueElementSize, sizeof(interactMessage_t));

	// Check if the queue was successfully created
	if (interactQueueHandle == NULL)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Queue could not be created.")));

		ESP.restart();
	}

	BaseType_t xReturned = xTaskCreatePinnedToCore(
		handleNetwork
		, "Network Task handler"
		, 5000 // Stack size
		, NULL  // Pass reference to a variable
		, tskIDLE_PRIORITY     // Priority
		, NULL,  // Task handle is not used here - simply pass NULL
		0
	);
	
	if (xReturned != pdPASS)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Task cannot be created.")));

		ESP.restart();
	}
}


bool isWifiConnected()
{
	return v_wifiConnected;
}

bool isWaitingHistory()
{
	return v_waitingHistory;
}


void sendInteractMessage(interactMessage_t &msg)
{
	// Check if the queue exists
	if (interactQueueHandle != NULL)
	{
		// The line needs to be passed as pointer to void.
		// The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
		// When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
		if (xQueueSend(interactQueueHandle, (void*)&msg, 0) == pdTRUE)
		{
			// The message was successfully sent.
			SerialDebug.log(LOG_LEVEL::DEBUG, String(F("Data sent into the Queue")));
			return;
		}
		else
		{
			// Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
			//   write into the same queue it can fill-up between the test and actual send attempt
			SerialDebug.log(LOG_LEVEL::DEBUG, String(F("Unable to send data into the Queue")));
		}
	}

	freeInteractMessage(msg);
}
