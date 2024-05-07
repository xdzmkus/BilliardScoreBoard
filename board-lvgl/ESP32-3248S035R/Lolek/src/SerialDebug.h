#ifndef _SERIAL_DEBUG_H_
#define _SERIAL_DEBUG_H_

#include <Arduino.h>

enum class LOG_LEVEL
{
	TRACE,
	INFO,
	WARN,
	ERROR,
	USER,
	NONE,
	DEBUG
};

class SerialDebugger
{
private:

	SemaphoreHandle_t serial_mutex = NULL;

public:

	void begin(unsigned long baud = 115200);

	void log(LOG_LEVEL level, String msg);
};

extern SerialDebugger SerialDebug;

#endif
