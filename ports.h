/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __PORTS_H__
#define __PORTS_H__


#include <Arduino.h>


#define VP_TEMP_0   V0
#define VP_TEMP_1   V1
#define VP_TEMP_2   V2
#define VP_TEMP_3   V3
#define VP_TEMP_4   V4

#define VP_HUM_0    V5
#define VP_HUM_1    V6
#define VP_HUM_2    V7
#define VP_HUM_3    V8
#define VP_HUM_4    V9


typedef struct {
    uint8_t TempPin;
    uint8_t HumPin;
} VirtDhtPin;


VirtDhtPin VirtDhtPins[] = {
    { VP_TEMP_0, VP_HUM_0 },
    { VP_TEMP_1, VP_HUM_1 },
    { VP_TEMP_2, VP_HUM_2 },
    { VP_TEMP_3, VP_HUM_3 }
};

uint8_t VirtDsPins[] = {
    VP_TEMP_0,
    VP_TEMP_1,
    VP_TEMP_2,
    VP_TEMP_3
};


#endif