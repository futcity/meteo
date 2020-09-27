/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

#include "ports.h"
#include "common.h"
#include "boards.h"
#include "narodmon.h"

/*
 * APPLICATION CLASSES
 */
SimpleTimer MainTimer;
SimpleTimer NarMonTimer;

/*
 * APPLICATION VARIABLES
 */
 int8_t NarMonTemp = 0;
 int8_t NarMonHum = 0;

/*
 * BLYNK CALLBACKS
 */
BLYNK_CONNECTED()
{
    Blynk.syncAll();
}

/*
 * OTHER FUNCTIONS
 */
void NarMonTimerCallback()
{
    SendToNarodmon(NarMonTemp, NarMonHum);
}

void MainTimerCallback()
{
    int8_t temp, hum;

    for (uint8_t i = 0; i < DS_PINS_COUNT; i++) {
        DsSensors[i]->requestTemperatures();
        temp = DsSensors[i]->getTempC(DEFAULT_DS_ADDR);
        Blynk.virtualWrite(VirtDsPins[i], temp);
#ifndef NAROD_MON_DHT_SENSOR
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
        }
#endif
    }

    for (uint8_t i = 0; i < DHT_PINS_COUNT; i++) {
        temp = DhtSensors[i]->getTemperature();
        hum = DhtSensors[i]->getHumidity();
        Blynk.virtualWrite(VirtDhtPins[i].TempPin, temp);
        Blynk.virtualWrite(VirtDhtPins[i].HumPin, hum);
#ifdef NAROD_MON_DHT_SENSOR
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
            NarMonHum = hum;
        }
#endif
    }
}

/*
 * APPLICATION MAIN FUNCTIONS
 */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, SERVER_ADDR, SERVER_PORT);

    for (uint8_t i = 0; i < DS_PINS_COUNT; i++) {
        DsSensors[i]->begin();
    }

    for (uint8_t i = 0; i < DHT_PINS_COUNT; i++) {
        DhtSensors[i]->setup(DhtPins[i], DHTesp::DHT22);
    }

    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
#ifdef NAROD_MON_ENABLED
    NarMonTimer.setInterval(NARMON_TMR_DELAY, NarMonTimerCallback);
#endif
}

void loop()
{
    Blynk.run();

    MainTimer.run();
#ifdef NAROD_MON_ENABLED
    NarMonTimer.run();
#endif
}
