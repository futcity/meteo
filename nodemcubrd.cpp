/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include <Arduino.h>

#include "boards.h"

#ifdef BOARD_NODEMCU_V1

#define DS_PIN_0    D5
#define DS_PIN_1    D6
#define DS_PIN_2    D7
#define DS_PIN_3    D8
#define DHT_PIN_0   D1
#define DHT_PIN_1   D2
#define DHT_PIN_2   D3
#define DHT_PIN_3   D4


DHTesp Dht0, Dht1, Dht2, Dht3;
OneWire Ow0(DS_PIN_0);
OneWire Ow1(DS_PIN_1);
OneWire Ow2(DS_PIN_2);
OneWire Ow3(DS_PIN_3);
DallasTemperature DsTemp0(&Ow0);
DallasTemperature DsTemp1(&Ow1);
DallasTemperature DsTemp2(&Ow2);
DallasTemperature DsTemp3(&Ow3);

uint8_t DhtPins[] = {
    DHT_PIN_0,
    DHT_PIN_1,
    DHT_PIN_2,
    DHT_PIN_3
};

DHTesp *DhtSensors[] = {
    &Dht0,
    &Dht1,
    &Dht2,
    &Dht3
};

DallasTemperature *DsSensors[] = {
    &DsTemp0,
    &DsTemp1,
    &DsTemp2,
    &DsTemp3
};

#endif