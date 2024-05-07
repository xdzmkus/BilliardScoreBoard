#pragma once

#include <Arduino.h>

typedef enum
{
	I_WIFI_ON,
	I_WIFI_OFF,
	I_MQTT_PUB,
	I_MQTT_SUB,
	I_MQTT_UNSUB,
	I_TELEGA_POLL,
	I_TELEGA_MSG_NEW,
	I_TELEGA_MSG_UPD,
} interactMsgType_t;

typedef struct
{
	char *msg;
	char *opt1;
	char *opt2;
	char *opt3;
} interactMessageBody_t;

typedef struct
{
	interactMsgType_t type;
	interactMessageBody_t body;
} interactMessage_t;


void setup_Interact();

bool isWifiConnected();
bool isWaitingHistory();

void sendInteractMessage(interactMessage_t &msg);

