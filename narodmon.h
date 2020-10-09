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
#define NAROD_MON_IP		"narodmon.ru"
#define NAROD_MON_PORT		8283
#define NAROD_MON_SENSOR	0

 extern int8_t NarMonTemp;
 extern int8_t NarMonHum;

/**
 * @brief Update narmon temperature
 * 
 * @param [in] temp Current temperature
 */
 void NarodmonSetTemp(int8_t temp);

/**
 * @brief Send data to narodmon server
 * 
 * @returns HTTP status
 */
bool SendToNarodmon();

#endif
