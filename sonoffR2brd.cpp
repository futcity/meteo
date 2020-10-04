/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_SONOFF_R2

#define DHT_PIN_0   3
#define DHT_PIN_1   1
#define DHT_PIN_2   2
#define DS_PIN_0    3
#define DS_PIN_1    1
#define DS_PIN_2    2
#define LED_PIN     13

uint8_t Led = LED_PIN;

#ifdef SENSOR_TYPE_DHT
DHTesp Dht0;
DHTesp Dht1;
DHTesp Dht2;

uint8_t DhtPins[] = {
    DHT_PIN_0,
    DHT_PIN_1,
    DHT_PIN_2
};

DHTesp *DhtSensors[] = {
    &Dht0,
    &Dht1,
    &Dht2
};
#endif

#ifdef SENSOR_TYPE_DALLAS
OneWire Ow0(DS_PIN_0);
OneWire Ow1(DS_PIN_1);
OneWire Ow2(DS_PIN_2);

DallasTemperature DsTemp0(&Ow0);
DallasTemperature DsTemp1(&Ow1);
DallasTemperature DsTemp2(&Ow2);

DallasTemperature *DsSensors[] = {
    &DsTemp0,
    &DsTemp1,
    &DsTemp2
};
#endif

#endif
