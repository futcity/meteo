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
#define BOARD_ESP_01
//#define BOARD_SONOFF_V2
//#define BOARD_SONOFF_V3

#define DHT_PINS_COUNT  1
#define DS_PINS_COUNT   0


extern uint8_t DhtPins[];
extern DHTesp *DhtSensors[];
extern DallasTemperature *DsSensors[];


#endif
