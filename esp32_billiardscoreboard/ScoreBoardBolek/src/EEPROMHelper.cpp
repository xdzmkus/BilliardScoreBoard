#include "EEPROMHelper.h"
#include "SerialDebug.h"

#include <EEPROM.h>

char ap_ssid[33] = {};
char ap_pass[33] = {};
char bot_token[65] = {};
char bot_channel[33] = {};
char greeting[97] = {};
char sta_ssid[33] = {};
char sta_pass[33] = {};
char mqtt_host[65] = {};
char mqtt_port[6] = {};
char mqtt_user[33] = {};
char mqtt_pass[33] = {};

class EEPROMHelper
{
public:

	static void begin(size_t size)
	{
		EEPROM.begin(size);
	}

	static String readEEPROM(int offset, unsigned int len)
	{
		String res = "";
		for (unsigned int i = 0; i < len; ++i)
		{
			res += char(EEPROM.read(i + offset));
		}
		SerialDebug.log(LOG_LEVEL::DEBUG, String(F("readEEPROM(): ")) + res);
		return res;
	}

	static void writeEEPROM(int offset, unsigned int len, String value)
	{
		SerialDebug.log(LOG_LEVEL::DEBUG, String(F("writeEEPROM(): ")) + value);
		for (unsigned int i = 0; i < len; ++i)
		{
			EEPROM.write(i + offset, i < value.length() ? value[i] : 0);
		}
	}

	static bool commit()
	{
		return EEPROM.commit();
	}

};

void saveEEPROMGreetingMsg()
{
	EEPROMHelper::writeEEPROM(160, 96, greeting);       // 160-255

	EEPROMHelper::commit();
}

void saveEEPROMParams()
{
	EEPROMHelper::writeEEPROM(0, 32, ap_ssid);          // 0-31
	EEPROMHelper::writeEEPROM(32, 32, ap_pass);         // 32-63
	EEPROMHelper::writeEEPROM(64, 64, bot_token);       // 64-127
	EEPROMHelper::writeEEPROM(128, 32, bot_channel);    // 128-159
	EEPROMHelper::writeEEPROM(320, 64, mqtt_host);      // 320-383
	EEPROMHelper::writeEEPROM(384, 5, mqtt_port);       // 384-388
	EEPROMHelper::writeEEPROM(389, 32, mqtt_user);      // 389-420
	EEPROMHelper::writeEEPROM(421, 32, mqtt_pass);      // 421-452

	EEPROMHelper::commit();
}

void saveEEPROMWifi()
{
	EEPROMHelper::writeEEPROM(256, 32, sta_ssid);       // 256-287
	EEPROMHelper::writeEEPROM(288, 32, sta_pass);       // 288-319

	EEPROMHelper::commit();
}

void loadEEPROM()
{
	EEPROMHelper::begin(453);

	EEPROMHelper::readEEPROM(0, 32).toCharArray(ap_ssid, 32);       // 0-31
	EEPROMHelper::readEEPROM(32, 32).toCharArray(ap_pass, 32);      // 32-63
	EEPROMHelper::readEEPROM(64, 64).toCharArray(bot_token, 64);    // 64-127
	EEPROMHelper::readEEPROM(128, 32).toCharArray(bot_channel, 32); // 128-159
	EEPROMHelper::readEEPROM(160, 96).toCharArray(greeting, 96);    // 160-255
	EEPROMHelper::readEEPROM(256, 32).toCharArray(sta_ssid, 32);    // 256-287
	EEPROMHelper::readEEPROM(288, 32).toCharArray(sta_pass, 32);    // 288-319
	EEPROMHelper::readEEPROM(320, 64).toCharArray(mqtt_host, 64);   // 320-383
	EEPROMHelper::readEEPROM(384, 5).toCharArray(mqtt_port, 5);     // 384-388
	EEPROMHelper::readEEPROM(389, 32).toCharArray(mqtt_user, 32);   // 389-420
	EEPROMHelper::readEEPROM(421, 32).toCharArray(mqtt_pass, 32);   // 421-452
}

void initEEPROM()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("EEPROM init"));

	EEPROMHelper::begin(453);

	EEPROMHelper::writeEEPROM(0, 32, "BOLEK");              // 0-31
	EEPROMHelper::writeEEPROM(32, 32, "password");          // 32-63
	EEPROMHelper::writeEEPROM(64, 64, "bot:token");         // 64-127
	EEPROMHelper::writeEEPROM(128, 32, "@channel");			// 128-159
	EEPROMHelper::writeEEPROM(160, 96, "BOLEK   <>   https://t.me/channel   <>   "); // 160-255
	EEPROMHelper::writeEEPROM(256, 32, "DIAMOND");			// 256-287
	EEPROMHelper::writeEEPROM(288, 32, "password");         // 288-319
	EEPROMHelper::writeEEPROM(320, 64, "mqtt.server.com");  // 320-383
	EEPROMHelper::writeEEPROM(384, 5, "1884");              // 384-388
	EEPROMHelper::writeEEPROM(389, 32, "bolek");            // 389-420
	EEPROMHelper::writeEEPROM(421, 32, "password");         // 421-452

	EEPROMHelper::commit();
}
