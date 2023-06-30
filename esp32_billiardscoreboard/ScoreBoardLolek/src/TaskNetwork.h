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

void setup_Network();

bool isConfigPortalStarted();
void startConfigPortal();
void stopConfigPortal();

bool isWifiConnected();
void startWiFi();
void stopWiFi();

bool isWaitMedicalResponse();
void sendMedicalRequest();
void revokeMedicalRequest();

void activateTelegram();
void deactivateTelegram();

void sendTelegaMessage(telegramMsgType_t type, String msg);
