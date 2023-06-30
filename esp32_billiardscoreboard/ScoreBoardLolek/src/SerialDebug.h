#ifndef _SERIAL_DEBUG_H_
#define _SERIAL_DEBUG_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum class LOG_LEVEL
{
	INFO,
	WARN,
	ERROR,
	DEBUG
};

class SerialDebugger
{
public:

	void begin(unsigned long baud = 115200);

	void log(LOG_LEVEL level, String msg);
};

extern SerialDebugger SerialDebug;

#endif
