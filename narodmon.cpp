/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include <ESP8266WiFi.h>

#include "narodmon.h"

int8_t NarMonTemp = 0;

static String GetDeviceID()
{
    String id = "ESP";

    for (auto c : WiFi.macAddress())
        if (c != ':')
            id += c;
    id.toUpperCase();

    return id;
}

void NarodmonSetTemp(int8_t temp)
{
    NarMonTemp = temp;
}

bool SendToNarodmon()
{
    WiFiClient  client;
    String      buf;

    buf = "#" + GetDeviceID() + "\n";
    buf += "#TEMP#" + String(NarMonTemp) + "\n";
    buf += "##\n";

    if (client.connect(NAROD_MON_IP, NAROD_MON_PORT)) {
        client.print(buf);
    } else {
        return false;
    }

    return true;
}
