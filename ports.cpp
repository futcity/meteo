/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "ports.h"
#include "common.h"

uint8_t VirtDsPins[] = {
    VP_TEMP_0,
    VP_TEMP_1
};

BLYNK_CONNECTED()
{
    Blynk.syncAll();
}
