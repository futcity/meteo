/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "ports.h"
#include "common.h"

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

BLYNK_CONNECTED()
{
    Blynk.syncAll();
}
