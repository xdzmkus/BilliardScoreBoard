#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

typedef enum
{
	T_COMMAND,
	T_POOL_MESSAGE,
	T_SNOOKER_MESSAGE_NEW,
	T_SNOOKER_MESSAGE_UPD,
} telegramMsgType_t;

#define MAX_LINE_LENGTH (255)

typedef struct
{
	telegramMsgType_t type;
	char line[MAX_LINE_LENGTH + 1];
} scoreMessage_t;

void setup_Network();

bool isConfigPortalStarted();
void startConfigPortal();
void stopConfigPortal();

bool isWifiConnected();
void startWiFi();
void stopWiFi();

bool isWaitingHistory();
void subscribeHistory();
void revokeHistory();

void publishCurrentState();

void sendTelegaMessage(telegramMsgType_t type, String msg);
