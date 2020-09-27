/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_ESP_01

#define DHT_PIN_0   2
#define DHT_PIN_1   0
#define DS_PIN_0    0
#define DS_PIN_1    2


DHTesp Dht0, Dht1;
OneWire Ow0(DS_PIN_0);
OneWire Ow1(DS_PIN_1);
DallasTemperature DsTemp0(&Ow0);
DallasTemperature DsTemp1(&Ow1);

uint8_t DhtPins[] = {
    DHT_PIN_0,
    DHT_PIN_1
};

DHTesp *DhtSensors[] = {
    &Dht0,
    &Dht1
};

DallasTemperature *DsSensors[] = {
    &DsTemp0,
    &DsTemp1
};

#endif