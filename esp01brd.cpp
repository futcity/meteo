/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_ESP_01

#define BUTTON_MAIN_PIN     3
#define LED_STATUS_PIN      1

#define MAIN_SENSOR_PIN     2
#define EXT_SENSOR_PIN      0

OneWire Ow(MAIN_SENSOR_PIN);
OneWire Ow2(EXT_SENSOR_PIN);
DallasTemperature TempMain(&Ow);
DallasTemperature TempExt(&Ow2);

uint8_t Buttons[] = {
    BUTTON_MAIN_PIN
};

uint8_t ButtonsCount = ARRAY_ITEMS_COUNT(Buttons);

uint8_t Leds[] = {
    LED_STATUS_PIN
};

uint8_t LedsCount = ARRAY_ITEMS_COUNT(Leds);

DallasTemperature *TempSensors[] = {
    &TempMain,
    &TempExt
};

uint8_t TempSensorsCount = ARRAY_ITEMS_COUNT(TempSensors);

void BoardInit()
{
    for (uint8_t i = 0; i < ButtonsCount; i++) {
        pinMode(Buttons[i], INPUT_PULLUP);
    }

    for (uint8_t i = 0; i < LedsCount; i++) {
        pinMode(Leds[i], OUTPUT);
    }

    for (uint8_t i = 0; i < TempSensorsCount; i++) {
        TempSensors[i]->begin();
    }
}

#endif