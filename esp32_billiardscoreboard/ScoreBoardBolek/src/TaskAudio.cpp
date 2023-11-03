#include "TaskAudio.h"
#include "SerialDebug.h"
#include "gui_main.h"

extern SemaphoreHandle_t mem_mutex;

#define SD_MISO 12
#define SD_MOSI 13
#define SD_SCLK 14
#define SD_SS   15

#define BCLK_PIN 26
#define DIN_PIN  25
#define LRC_PIN  27
#define SD_PIN   33

#include <FS.h>
#include <SD.h>
#include <SPI.h>

SPIClass SDSPI(HSPI);

#include <AudioFileSourceSD.h>
#include <AudioFileSourceID3.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

QueueHandle_t QueueHandle = NULL;
const uint8_t QueueElementSize = 16;

typedef struct {
    int16_t say;
} sayMessage_t;

#define SAY_LOLEK 1000
#define SAY_BOLEK 1001
#define SAY_BYE 1002
#define SAY_GAME 1003
#define SAY_FRAME 1004
#define SAY_MIN -255
#define SAY_MAX 255

static void playMP3(const char* filename)
{
    // Try to take the mutex
    if (xSemaphoreTake(mem_mutex, portMAX_DELAY) == pdTRUE)
    {
        SerialDebug.log(LOG_LEVEL::INFO, String(F("Play: ")) + filename);

        AudioOutputI2S out;

        out.SetPinout(BCLK_PIN, LRC_PIN, DIN_PIN);

        AudioFileSourceSD file(filename);
        AudioFileSourceID3 id3(&file);
        AudioGeneratorMP3 mp3;

        mp3.begin(&id3, &out);

        while (mp3.isRunning())
        {
            if (!mp3.loop()) mp3.stop();
        }

        xSemaphoreGive(mem_mutex); // After accessing the shared resource give the mutex and allow other processes to access it
    }
}

static void handleAudio(void* pvParameters)
{
    for (;;)
    {
        sayMessage_t message;

        int ret = xQueueReceive(QueueHandle, &message, portMAX_DELAY);
        if (ret == pdPASS)
        {
            if (message.say == SAY_LOLEK)
            {
                playMP3("/lolek.mp3");
            }
            else if (message.say == SAY_BOLEK)
            {
                playMP3("/bolek.mp3");
            }
            else if (message.say == SAY_BYE)
            {
                playMP3("/bye.mp3");
            }
            else if (message.say == SAY_GAME)
            {
                playMP3("/game.mp3");
            }
            else if (message.say == SAY_FRAME)
            {
                playMP3("/frame.mp3");
            }
            else if (message.say < 0 && message.say >= SAY_MIN)
            {
                String fileName = "/m";
                fileName += abs(message.say);
                fileName += ".mp3";

                playMP3(fileName.c_str());
            }
            else if (message.say >= 0 && message.say <= SAY_MAX)
            {
                String fileName = "/";
                fileName += message.say;
                fileName += ".mp3";

                playMP3(fileName.c_str());
            }
        }
        else if (ret == pdFALSE)
        {
            SerialDebug.log(LOG_LEVEL::DEBUG, String(F("Unable to receive data from the Queue")));
        }

        SerialDebug.log(LOG_LEVEL::INFO, String(F("AUDIO Stack water mark: ")) + uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(1);
    }
}

static void say(int16_t word)
{
    if (!isAudio) return;

    sayMessage_t message = { .say = word };

    // Check if there is any free space in the queue
    if (QueueHandle && uxQueueSpacesAvailable(QueueHandle) > 0)
    {
        // The line needs to be passed as pointer to void.
        // The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
        // When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
        int ret = xQueueSend(QueueHandle, (void*)&message, 0);
        if (ret == pdTRUE)
        {
            // The message was successfully sent.
        }
        else if (ret == errQUEUE_FULL)
        {
            // Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
            //   write into the same queue it can fill-up between the test and actual send attempt
            SerialDebug.log(LOG_LEVEL::DEBUG, String(F("Unable to send data into the Queue")));
        }
    }
}

bool setup_SDCARD()
{
    pinMode(SD_SS, OUTPUT);
    digitalWrite(SD_SS, HIGH);

    SDSPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_SS);

    if (!SD.begin(SD_SS, SDSPI))
    {
        SerialDebug.log(LOG_LEVEL::ERROR, F("Card Mount Failed"));
        return false;
    }

    SerialDebug.log(LOG_LEVEL::INFO, F("SD card mounted."));

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, F("No SD card attached"));
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

void setup_Audio()
{
    SerialDebug.log(LOG_LEVEL::INFO, F("Setup Audio Task"));

    pinMode(SD_PIN, OUTPUT_OPEN_DRAIN);
    digitalWrite(SD_PIN, LOW);
    
    audioLogger = &Serial;

    // Create the queue which will have <QueueElementSize> number of elements, each of size `sayMessage_t` and pass the address to <QueueHandle>.
    QueueHandle = xQueueCreate(QueueElementSize, sizeof(sayMessage_t));

    // Check if the queue was successfully created
    if (QueueHandle == NULL)
    {
        SerialDebug.log(LOG_LEVEL::ERROR, String(F("Queue could not be created.")));

        ESP.restart();
    }
    
    xTaskCreatePinnedToCore(
        handleAudio
        , "Audio handler"
        , 5000  // Stack size
        , NULL  // Pass reference to a variable
        , 1     // Priority
        , NULL  // Task handle is not used here - simply pass NULL
        , 0 // Core on which the task will run
    );
}

void audio_turnOn()
{
    digitalWrite(SD_PIN, HIGH);

    say(SAY_BOLEK);
}

void audio_turnOff()
{
   digitalWrite(SD_PIN, LOW);

   if (QueueHandle)
       xQueueReset(QueueHandle);
}

void sayLot(int16_t lot)
{
    say(lot);
}

void sayGameResult(int16_t first, int16_t second)
{
    say(SAY_GAME);
    say(first);
    say(second);
}

void sayGameResult(int16_t first, int16_t second, int16_t third)
{
    say(SAY_GAME);
    say(first);
    say(second);
    say(third);
}

void sayFrameResult(int16_t first, int16_t second)
{
    say(SAY_FRAME);
    say(first);
    say(second);
}
