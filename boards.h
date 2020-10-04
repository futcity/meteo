/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <DHTesp.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define BOARD_NODEMCU_V1
//#define BOARD_ESP_01
#define BOARD_SONOFF_R2
//#define BOARD_SONOFF_V3

//#define SENSOR_TYPE_DHT
#define SENSOR_TYPE_DALLAS

#define SENSORS_COUNT  3

#ifdef SENSOR_TYPE_DHT
extern uint8_t DhtPins[];
extern DHTesp *DhtSensors[];
#endif

#ifdef SENSOR_TYPE_DALLAS
extern DallasTemperature *DsSensors[];
#endif

extern uint8_t Led;

#endif
