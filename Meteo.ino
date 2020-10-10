/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "ports.h"
#include "common.h"
#include "boards.h"
#include "narodmon.h"
#include "meteo.h"

/*
 * APPLICATION CLASSES
 */
SimpleTimer MainTimer;
SimpleTimer NarMonTimer;

/*
 * OTHER FUNCTIONS
 */
static void ButtonRead()
{
    if (digitalRead(Buttons[MAIN_BUTTON]) == LOW) {
        ESP.reset();
        delay(600);
    }
}

static void NarMonTimerCallback()
{
    SendToNarodmon();
}

static void MainTimerCallback()
{
    MeteoGetTemp();
}

/*
 * APPLICATION MAIN FUNCTIONS
 */
void setup()
{
    BoardInit();
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, SERVER_ADDR, SERVER_PORT);
    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
#ifdef NAROD_MON_ENABLED
    NarMonTimer.setInterval(NARMON_TMR_DELAY, NarMonTimerCallback);
#endif
}

void loop()
{
    Blynk.run();

    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(Leds[STATUS_LED], HIGH);
    } else {
        digitalWrite(Leds[STATUS_LED], LOW);
    }

    ButtonRead();

    MainTimer.run();
#ifdef NAROD_MON_ENABLED
    NarMonTimer.run();
#endif
}
