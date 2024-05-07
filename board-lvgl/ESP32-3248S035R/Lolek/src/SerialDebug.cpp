#define SERIAL_DEBUG

#include "SerialDebug.h"

#include <HardwareSerial.h>

void SerialDebugger::begin(unsigned long baud)
{
#ifdef SERIAL_DEBUG

	Serial.begin(baud);

	serial_mutex = xSemaphoreCreateMutex(); // Create the mutex

	if (serial_mutex == NULL)
	{
		Serial.println(F("Cannot create Mutex"));

		ESP.restart();
	}

#endif
}

void SerialDebugger::log(LOG_LEVEL level, String msg)
{
#ifdef SERIAL_DEBUG

	String msg_keyword;

	switch (level)
	{
	case LOG_LEVEL::INFO:
		msg_keyword = "INFO: ";
		break;
	case LOG_LEVEL::WARN:
		msg_keyword = "WARNING: ";
		break;
	case LOG_LEVEL::ERROR:
		msg_keyword = "ERROR: ";
		break;
	case LOG_LEVEL::TRACE:
		msg_keyword = "TRACE: ";
		break;
	case LOG_LEVEL::DEBUG:
		msg_keyword = "DEBUG: ";
		break;
	case LOG_LEVEL::USER:
		msg_keyword = "USER: ";
		break;
	default:
		return;
	}

	msg_keyword += msg;

	if (xSemaphoreTake(serial_mutex, portMAX_DELAY) == pdTRUE)
	{
		Serial.println(msg_keyword);

		xSemaphoreGive(serial_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

#endif
}

SerialDebugger SerialDebug;