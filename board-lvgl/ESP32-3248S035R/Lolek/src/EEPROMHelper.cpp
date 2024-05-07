#include "EEPROMHelper.h"
#include "SerialDebug.h"
#include "defs.h"

#include <EEPROM.h>

class EEPROMHelper
{
public:
	static void begin(size_t size)
	{
		EEPROM.begin(size);
	}

	static void readEEPROM(int offset, unsigned int len, char *boardData)
	{
		for (unsigned int i = 0; i < len; i++)
		{
			boardData[i] = static_cast<char>(EEPROM.read(i + offset));
		}
	}

	static void writeEEPROM(int offset, unsigned int len, char *boardData)
	{
		for (unsigned int i = 0; i < len; i++)
		{
			EEPROM.write(i + offset, boardData[i]);
		}
	}

	static bool commit()
	{
		return EEPROM.commit();
	}
};

void saveEEPROMdata()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("EEPROM save"));

	EEPROMHelper::begin(sizeof(BOARD_EEPROM_DATA));
	EEPROMHelper::writeEEPROM(0, sizeof(BOARD_EEPROM_DATA), reinterpret_cast<char*>(&boardEEPROMdata));
	EEPROMHelper::commit();
}
void loadEEPROMdata()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("EEPROM load"));

	EEPROMHelper::begin(sizeof(BOARD_EEPROM_DATA));
	EEPROMHelper::readEEPROM(0, sizeof(BOARD_EEPROM_DATA), reinterpret_cast<char*>(&boardEEPROMdata));
}
