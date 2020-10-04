/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <ESP8266WiFi.h>
#include <BlynkEsp8266.h>

#define DEVICE_KEY  ""

#define WIFI_SSID   ""
#define WIFI_PASSWD ""

#define SERVER_ADDR	""
#define SERVER_PORT 8080

#define MAIN_TMR_DELAY      5000
#define NARMON_TMR_DELAY    120000
#define SERIAL_SPEED        9600
#define DEFAULT_DS_ADDR     0
#define DS_ERROR_VALUE		-127
#define RETRIES_COUNT		10

extern BlynkWifi Blynk;

#endif
