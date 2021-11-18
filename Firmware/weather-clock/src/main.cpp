#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

#include "TimeUtil.h"
#include "TftDisplay.h"
#include "CityWeather.h"

WiFiUDP *TimeUtil::wifiUdp = nullptr;
TimeUtil *TimeUtil::instance = nullptr;
TftDisplay *TftDisplay::instance = nullptr;
CityWeather *CityWeather::instance = nullptr;

void setup()
{
    Serial.begin(115200);
    EEPROM.begin(1024);

    TftDisplay *tftDisplay = TftDisplay::getInstance();

    WiFi.begin("kanglu", "zxcvbnm123");
    while (WiFi.status() != WL_CONNECTED) {
        if (tftDisplay->loading(30) >= 194) {
            //TODO web配网
            Serial.println("连接wifi失败！");
        }
    }

    //走进度条完动画
    while (tftDisplay->loading(30) < 194);
    Serial.println("连接wifi成功！");

    //显示天气信息
    TftDisplay::getInstance()->displayWeather();

    TimeUtil *timeUtil = TimeUtil::getInstance();
}

bool prevTime = false;
time_t prevDisplay = 0;

void loop()
{
    if (now() != prevDisplay) {
        prevDisplay = now();
        TftDisplay::getInstance()->displayDigitalClock();
        prevTime=false;
    }

    if (second() % 2 == 0 && !prevTime) {
        TftDisplay::getInstance()->scrollBanner();
        prevTime = true;
    }

    TftDisplay::getInstance()->displaySpaceman();
}