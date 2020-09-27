/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include <ESP8266WiFi.h>

#include "narodmon.h"


static String GetDeviceID()
{
    String id = "E";

    for (auto c : WiFi.macAddress())
        if (c != ':')
            id += c;
    id.toUpperCase();

    return id;
}

bool SendToNarodmon(int8_t temp, int8_t hum)
{
    WiFiClient  client;
    String      buf;

    buf = "#" + GetDeviceID() + "\n";
    buf += "#TEMP#" + String(temp) + "\n";
#ifdef NAROD_MON_DHT_SENSOR
    buf += "#HUM#" + String(hum) + "\n";
#endif
    buf += "##\n";

    if (client.connect(NAROD_MON_IP, NAROD_MON_PORT)) {
        client.print(buf);
    } else {
        return false;
    }

    return true;
}