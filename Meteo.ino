/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHTesp.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*
 * DEVICE HARDWARE
 */
#define DEVICE_NODEMCU_V1
//#define DEVICE_SONOFF_V2
//#define DEVICE_SONOFF_V3

//#define NAROD_MON_ENABLED

/*
 * APPLICATION DEFINES
 */
#define DEVICE_KEY  ""

#define WIFI_SSID   ""
#define WIFI_PASSWD ""

#define SERVER_ADDR ""
#define SERVER_PORT 8080

#define MAIN_TMR_DELAY      4000
#define NARMON_TMR_DELAY    120000
#define SERIAL_SPEED        9600
#define DEFAULT_DS_ADDR     0

#define NAROD_MON_IP            "narodmon.ru"
#define NAROD_MON_PORT          8283
#define NAROD_MON_SENSOR        0
#define NAROD_MON_DHT_SENSOR

/*
 * VIRTUAL PINS DEFINES
 */
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

/*
 * GPIO DEFINES
 */
#ifdef DEVICE_NODEMCU_V1
#define DHT_PINS_COUNT  1
#define DS_PINS_COUNT   0

#define DS_PIN_0    D5
#define DS_PIN_1    D6
#define DS_PIN_2    D7
#define DS_PIN_3    D8

#define DHT_PIN_0   D1
#define DHT_PIN_1   D2
#define DHT_PIN_2   D3
#define DHT_PIN_3   D4
#endif

typedef struct {
    uint8_t TempPin;
    uint8_t HumPin;
} VirtDhtPin;

/*
 * APPLICATION CLASSES
 */
SimpleTimer MainTimer;
SimpleTimer NarMonTimer;
DHTesp Dht0, Dht1, Dht2, Dht3;
OneWire Ow0(DS_PIN_0);
OneWire Ow1(DS_PIN_1);
OneWire Ow2(DS_PIN_2);
OneWire Ow3(DS_PIN_3);
DallasTemperature DsTemp0(&Ow0);
DallasTemperature DsTemp1(&Ow1);
DallasTemperature DsTemp2(&Ow2);
DallasTemperature DsTemp3(&Ow3);

/*
 * APPLICATION VARIABLES
 */
 int8_t NarMonTemp = 0;
 int8_t NarMonHum = 0;

uint8_t DhtPins[] = {
    DHT_PIN_0,
    DHT_PIN_1,
    DHT_PIN_2,
    DHT_PIN_3
};

DHTesp *DhtSensors[] = {
    &Dht0,
    &Dht1,
    &Dht2,
    &Dht3
};

DallasTemperature *DsSensors[] = {
    &DsTemp0,
    &DsTemp1,
    &DsTemp2,
    &DsTemp3
};

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

/*
 * BLYNK CALLBACKS
 */
BLYNK_CONNECTED()
{
    Blynk.syncAll();
}

/*
 * OTHER FUNCTIONS
 */
String GetDeviceID()
{
    String id = "E";

    for (auto c : WiFi.macAddress())
        if (c != ':')
            id += c;
    id.toUpperCase();

    return id;
}

bool SendToNarodmon(String host, int8_t temp, int8_t hum)
{
    WiFiClient  client;
    String      buf;

    buf = "#" + host + "\n";
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

void NarMonTimerCallback()
{
    SendToNarodmon(GetDeviceID(), NarMonTemp, NarMonHum);
}

void MainTimerCallback()
{
    int8_t temp, hum;

    for (uint8_t i = 0; i < DS_PINS_COUNT; i++) {
        DsSensors[i]->requestTemperatures();
        temp = DsSensors[i]->getTempC(DEFAULT_DS_ADDR);
        Blynk.virtualWrite(VirtDsPins[i], temp);
#ifndef NAROD_MON_DHT_SENSOR
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
        }
#endif
    }

    for (uint8_t i = 0; i < DHT_PINS_COUNT; i++) {
        temp = DhtSensors[i]->getTemperature();
        hum = DhtSensors[i]->getHumidity();
        Blynk.virtualWrite(VirtDhtPins[i].TempPin, temp);
        Blynk.virtualWrite(VirtDhtPins[i].HumPin, hum);
#ifdef NAROD_MON_DHT_SENSOR
        if (i == NAROD_MON_SENSOR) {
            NarMonTemp = temp;
            NarMonHum = hum;
        }
#endif
    }
}

/*
 * APPLICATION MAIN FUNCTIONS
 */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, SERVER_ADDR, SERVER_PORT);

    for (uint8_t i = 0; i < DS_PINS_COUNT; i++) {
        DsSensors[i]->begin();
    }

    for (uint8_t i = 0; i < DHT_PINS_COUNT; i++) {
        DhtSensors[i]->setup(DhtPins[i], DHTesp::DHT22);
    }

    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
#ifdef NAROD_MON_ENABLED
    NarMonTimer.setInterval(NARMON_TMR_DELAY, NarMonTimerCallback);
#endif
}

void loop()
{
    Blynk.run();

    MainTimer.run();
#ifdef NAROD_MON_ENABLED
    NarMonTimer.run();
#endif
}
