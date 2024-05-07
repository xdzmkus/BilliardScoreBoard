#include "defs.h"
#include "TaskAudio.h"
#include "SerialDebug.h"
#include "gui.h"

#include <FS.h>
#include <SD.h>

#include <AudioFileSourceSD.h>
#include <AudioFileSourceID3.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

#include <ClockTimer.hpp>

static QueueHandle_t audioQueueHandle = NULL;
static const uint8_t audioQueueElementSize = 8;

static volatile bool isAudio = false;

typedef struct
{
	int16_t say;
} sayMessage_t;

static void playMP3(const char* filename)
{
	SerialDebug.log(LOG_LEVEL::INFO, String(F("Play: ")) + filename);

	AudioOutputI2S out;

	out.SetPinout(BCLK_PIN, LRC_PIN, DIN_PIN);

	// Try to take the mutex
	if (xSemaphoreTake(gui_mutex, portMAX_DELAY) == pdTRUE)
	{
		out.SetGain(gui_getVolumeInRange(0.1, 3.5));

		xSemaphoreGive(gui_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
	}

	AudioFileSourceSD file(filename);
	AudioFileSourceID3 id3(&file);
	AudioGeneratorMP3 mp3;

	if(mp3.begin(&id3, &out))
	{
		while (mp3.isRunning())
		{
			if(!mp3.loop()) mp3.stop();
			vTaskDelay(1);
		}
	}
}

static void handleAudio(void* pvParameters)
{
	ArduLibs::MillisTimer waterMarkTimer(60000); // 60 sec
	waterMarkTimer.start();

	for (;;)
	{
		sayMessage_t message;

		int ret = xQueueReceive(audioQueueHandle, &message, 0);
		if (ret == pdTRUE)
		{
			String fileName = "/";

			if (message.say == SAY_LOLEK)
			{
				fileName += "lolek.mp3";
			}
			else if (message.say == SAY_BOLEK)
			{
				fileName += "bolek.mp3";
			}
			else if (message.say == SAY_GAME)
			{
				fileName += "game.mp3";
			}
			else if (message.say == SAY_FRAME)
			{
				fileName += "frame.mp3";
			}
			else if (message.say < 0 && message.say >= SAY_MIN)
			{
				fileName += "m";
				fileName += abs(message.say);
				fileName += ".mp3";
			}
			else if (message.say >= 0 && message.say <= SAY_MAX)
			{
				fileName += message.say;
				fileName += ".mp3";
			}
			else
			{
				fileName += "bye.mp3";
			}

			playMP3(fileName.c_str());
		}

		if (waterMarkTimer.isReady())
		{
			SerialDebug.log(LOG_LEVEL::DEBUG, String(F("AUDIO Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));
		}

//		vTaskDelay(1);
	}
}

static bool mount_SDCARD()
{
	pinMode(SD_SS, OUTPUT);
	digitalWrite(SD_SS, HIGH);

	// SDSPI.begin();
	SDSPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_SS);

	if (!SD.begin(SD_SS, SDSPI))
	{
		SerialDebug.log(LOG_LEVEL::ERROR, F("Card Mount Failed"));
		SDSPI.end();
		return false;
	}

	SerialDebug.log(LOG_LEVEL::INFO, F("SD card mounted."));

	uint8_t cardType = SD.cardType();

	if (cardType == CARD_NONE)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, F("No SD card attached"));
		SD.end();
		SDSPI.end();
		return false;
	}

	SerialDebug.log(LOG_LEVEL::DEBUG, F("SD Card Type: "));

	if (cardType == CARD_MMC)
	{
		SerialDebug.log(LOG_LEVEL::DEBUG, F("MMC"));
	}
	else if (cardType == CARD_SD)
	{
		SerialDebug.log(LOG_LEVEL::DEBUG, F("SDSC"));
	}
	else if (cardType == CARD_SDHC)
	{
		SerialDebug.log(LOG_LEVEL::DEBUG, F("SDHC"));
	}
	else
	{
		SerialDebug.log(LOG_LEVEL::DEBUG, F("UNKNOWN"));
	}

	return true;
}

bool setup_Audio()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Setup Audio Task"));

	pinMode(BCLK_PIN, OUTPUT);
	pinMode(DIN_PIN, OUTPUT);
	pinMode(LRC_PIN, OUTPUT);

#ifdef SD_PIN
	pinMode(SD_PIN, OUTPUT_OPEN_DRAIN);
	digitalWrite(SD_PIN, LOW);
#endif

	// Create the queue which will have <QueueElementSize> number of elements, each of size `sayMessage_t` and pass the address to <QueueHandle>.
	audioQueueHandle = xQueueCreate(audioQueueElementSize, sizeof(sayMessage_t));

	// Check if the queue was successfully created
	if (audioQueueHandle == NULL)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Queue cannot be created.")));

		ESP.restart();
	}

	if (!mount_SDCARD()) return false; // Failed to mount SD card

	BaseType_t xReturned = xTaskCreatePinnedToCore(
		handleAudio
		, "Audio handler"
		, 4000  // Stack size
		, NULL  // Pass reference to a variable
		, tskIDLE_PRIORITY + 1   // Priority
		, NULL  // Task handle
		, 1 // Core on which the task will run
	);

	if (xReturned != pdPASS)
	{
		SerialDebug.log(LOG_LEVEL::ERROR, String(F("Task cannot be created.")));

		ESP.restart();
	}

	return true;
}

void audio_turnOn()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Turn Audio On"));

#ifdef SD_PIN
	digitalWrite(SD_PIN, HIGH);
#endif

	audio_reset();

	isAudio = true;
}

void audio_turnOff()
{
	SerialDebug.log(LOG_LEVEL::INFO, F("Turn Audio Off"));

	isAudio = false;

	audio_reset();

#ifdef SD_PIN
	digitalWrite(SD_PIN, LOW);
#endif
}

void audio_reset()
{
	if (audioQueueHandle) xQueueReset(audioQueueHandle);
}

void audio_say(int16_t word)
{
	if (!isAudio) return;

	sayMessage_t message = { .say = word };

	// Check if there is any free space in the queue
	if (uxQueueSpacesAvailable(audioQueueHandle) > 0)
	{
		// The line needs to be passed as pointer to void.
		// The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
		// When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
		int ret = xQueueSend(audioQueueHandle, (void*)&message, 0);
		if (ret == pdTRUE)
		{
			// The message was successfully sent.
		}
		else if (ret == errQUEUE_FULL)
		{
			// Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
			//   write into the same queue it can fill-up between the test and actual send attempt
			SerialDebug.log(LOG_LEVEL::WARN, String(F("Unable to send data into the Queue")));
		}
	}
}

