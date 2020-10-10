/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __METEO_H__
#define __METEO_H__

#include <Arduino.h>

#include "meteo.h"
#include "narodmon.h"
#include "boards.h"
#include "common.h"
#include "ports.h"

void MeteoGetTemp()
{
    int8_t temp;

    for (uint8_t i = 0; i < TempSensorsCount; i++) {
        for (uint8_t j = 0; j < RETRIES_COUNT; j++) {
            TempSensors[i]->requestTemperatures();
            temp = TempSensors[i]->getTempCByIndex(DEFAULT_DS_ADDR);
            if (temp != DS_ERROR_VALUE) {
                break;
            }
            delay(100);
        }

        Blynk.virtualWrite(VirtDsPins[i], temp);

#ifdef NAROD_MON_ENABLED
        if (i == NAROD_MON_SENSOR) {
            NarodmonSetTemp(temp);
        }
#endif
    }
}

#endif
