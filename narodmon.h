/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __NARODMON_H__
#define __NARODMON_H__


#include <Arduino.h>


#define NAROD_MON_ENABLED
#define NAROD_MON_DHT_SENSOR
#define NAROD_MON_IP		"narodmon.ru"
#define NAROD_MON_PORT		8283
#define NAROD_MON_SENSOR	0

/**
 * @brief Send data to narodmon server
 * 
 * @param temp Sending temperature
 * @param hum Sending humidity
 * 
 * @returns HTTP status
 */
bool SendToNarodmon(int8_t temp, int8_t hum);


#endif