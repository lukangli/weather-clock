#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "TimeUtils.h"
#include "TftDisplay.h"
#include "CityWeather.h"
#include "EepromUtils.h"
#include "WebConfig.h"

WiFiUDP *TimeUtils::wifiUdp = nullptr;
TimeUtils *TimeUtils::instance = nullptr;
TftDisplay *TftDisplay::instance = nullptr;
CityWeather *CityWeather::instance = nullptr;
EepromUtils *EepromUtils::instance = nullptr;
WebConfig *WebConfig::instance = nullptr;

void setup()
{
    Serial.begin(115200);

    TftDisplay *tftDisplay = TftDisplay::getInstance();

    WiFi.begin("", "");
    while (WiFi.status() != WL_CONNECTED) {
        if (tftDisplay->loading(30) >= 194) {
            TftDisplay::getInstance()->displayWebConfig();
            WebConfig::getInstance()->webConfigInit();
            Serial.println("连接wifi失败！");
        }
    }

    //走进度条完动画
    while (tftDisplay->loading(30) < 194);
    Serial.println("连接wifi成功！");

    //显示天气信息
    TftDisplay::getInstance()->displayWeather();

    TimeUtils *timeUtil = TimeUtils::getInstance();
}

bool prevTime = false;
time_t prevDisplay = 0;

void loop()
{
    //更新时钟
    if (now() != prevDisplay) {
        prevDisplay = now();
        TftDisplay::getInstance()->displayDigitalClock();
        prevTime=false;
    }

    //更新天气信息
    if (second() % 2 == 0 && !prevTime) {
        TftDisplay::getInstance()->scrollBanner();
        prevTime = true;
    }

    TftDisplay::getInstance()->displaySpaceman();
}