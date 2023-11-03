#ifndef _EEPROM_HELPER_H_
#define _EEPROM_HELPER_H_

extern char ap_ssid[33];
extern char ap_pass[33];
extern char bot_token[65];
extern char bot_channel[33];
extern char greeting[97];
extern char sta_ssid[33];
extern char sta_pass[33];
extern char mqtt_host[65];
extern char mqtt_port[6];
extern char mqtt_user[33];
extern char mqtt_pass[33];

void saveEEPROMGreetingMsg();
void saveEEPROMParams();
void saveEEPROMWifi();
void loadEEPROM();
void initEEPROM();

#endif
