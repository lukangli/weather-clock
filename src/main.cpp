#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

#include "TftDisplay.h"
#include "CityWeather.h"
TftDisplay* TftDisplay::instance = nullptr;
CityWeather* CityWeather::instance = nullptr;

void setup() {
    Serial.begin(115200);
    EEPROM.begin(1024);

    TftDisplay*  tftDisplay  = TftDisplay::getInstance();
    CityWeather* cityWeather = CityWeather::getInstance();

    WiFi.begin("kanglu", "zxcvbnm123");
    while (WiFi.status() != WL_CONNECTED) {
        if (tftDisplay->loading(30) >= 194) {
            //web配网
            Serial.println("连接wifi失败！");
        }
    }

    //走完动画
    while (tftDisplay->loading(30) < 194);
    Serial.println("连接wifi成功！");

    tftDisplay->displayTempHumidity();
    cityWeather->getCityCode();
}

void loop() {
    delay(2000);
    Serial.println("clion hello!");
}