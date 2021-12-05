#include <Ticker.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "TimeUtils.h"
#include "TftDisplay.h"
#include "CityWeather.h"
#include "EepromUtils.h"
#include "WebConfig.h"

WiFiUDP *TimeUtils::wifiUdp = nullptr;
TimeUtils *TimeUtils::instance = nullptr;
WebConfig *WebConfig::instance = nullptr;
TftDisplay *TftDisplay::instance = nullptr;
CityWeather *CityWeather::instance = nullptr;
EepromUtils *EepromUtils::instance = nullptr;

Ticker flipper;  //实例化定时器对象

void setup()
{
    Serial.begin(115200);

    TftDisplay *tftDisplay = TftDisplay::getInstance();

    WiFi.begin("", "");
    while (WiFi.status() != WL_CONNECTED) {
        if (tftDisplay->loading(10) >= 194) {
            TftDisplay::getInstance()->displayWebConfig();
            WebConfig::getInstance()->webConfigInit();
            break;
        }
    }

    //走进度条完动画
    while (tftDisplay->loading(10) < 194);
    Serial.println("连接wifi成功！");

    //清屏并显示图标
    TftDisplay::getInstance()->displayTempHumidity();

    //显示天气信息
    TftDisplay::getInstance()->displayWeather();

    TimeUtils *timeUtil = TimeUtils::getInstance();
}

bool prevTime = false;
time_t prevDisplay = 0;
uint64_t weatherTime = 0;
void loop()
{
    //更新时钟
    if (now() != prevDisplay) {
        prevDisplay = now();
        TftDisplay::getInstance()->displayDigitalClock();
        prevTime=false;
    }

    //滚动栏
    if (second() % 2 == 0 && !prevTime) {
        TftDisplay::getInstance()->scrollBanner();
        prevTime = true;
    }

    //5分钟更新一次天气
    if(millis() - weatherTime > 300000){
        weatherTime = millis();
        TftDisplay::getInstance()->displayWeather();
    }

    TftDisplay::getInstance()->displaySpaceman();
}