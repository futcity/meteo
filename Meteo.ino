/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

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
 * OTHER FUNCTIONS
 */
void NarMonTimerCallback()
{
    SendToNarodmon(NarMonTemp, NarMonHum);
}

void MainTimerCallback()
{
    int8_t temp, hum;

#ifdef SENSOR_TYPE_DALLAS
    for (uint8_t i = 0; i < SENSORS_COUNT; i++) {
        for (uint8_t j = 0; j < RETRIES_COUNT; j++) {
            DsSensors[i]->requestTemperatures();
            temp = DsSensors[i]->getTempCByIndex(DEFAULT_DS_ADDR);
            if (temp != DS_ERROR_VALUE) {
                break;
            }
        }

        Blynk.virtualWrite(VirtDsPins[i], temp);

#ifdef NAROD_MON_ENABLED
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
        }
#endif
    }
#endif

#ifdef SENSOR_TYPE_DHT
    for (uint8_t i = 0; i < DHT_PINS_COUNT; i++) {
        for (uint8_t j = 0; j < RETRIES_COUNT; j++) {
            temp = DhtSensors[i]->getTemperature();
            hum = DhtSensors[i]->getHumidity();
            if (hum > 1)
                break;
        }

        Blynk.virtualWrite(VirtDhtPins[i].TempPin, temp);
        Blynk.virtualWrite(VirtDhtPins[i].HumPin, hum);

#ifdef NAROD_MON_ENABLED
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
            NarMonHum = hum;
        }
#endif
    }
#endif
}

/*
 * APPLICATION MAIN FUNCTIONS
 */
void setup()
{
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, SERVER_ADDR, SERVER_PORT);

    for (uint8_t i = 0; i < SENSORS_COUNT; i++) {
#ifdef SENSOR_TYPE_DALLAS
        DsSensors[i]->begin();
#endif

#ifdef SENSOR_TYPE_DHT
        DhtSensors[i]->setup(DhtPins[i], DHTesp::DHT22);
#endif
    }

    pinMode(Led, OUTPUT);

    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
#ifdef NAROD_MON_ENABLED
    NarMonTimer.setInterval(NARMON_TMR_DELAY, NarMonTimerCallback);
#endif
}

void loop()
{
    Blynk.run();

    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(Led, LOW);
    } else {
        digitalWrite(Led, HIGH);
    }

    MainTimer.run();
#ifdef NAROD_MON_ENABLED
    NarMonTimer.run();
#endif
}
