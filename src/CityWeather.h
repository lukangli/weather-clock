//
// Created by lukang on 2021/10/27.
//

#ifndef WEATHERCLOCK_CITYWEATHER_H
#define WEATHERCLOCK_CITYWEATHER_H

#include <ESP8266HTTPClient.h>

typedef struct displayInfo {
    int tempnum = 0;   //温度百分比
    int huminum = 0;   //湿度百分比
    int tempcol = 0xffff;   //温度显示颜色
    int humicol = 0xffff;   //湿度显示颜色
    int weatherCode = 0;
    String cityName;
    String aqi;
    uint16_t pm25V;
    uint32_t pm25BgColor;
    int32_t weatherIcon;
    String scrollText[7]; //滚动显示
} DisplayInfo;

typedef enum {
    FAILED = 0,
    SUCCESS
} ErrorStatus;

class CityWeather {
private:
    CityWeather() {
        cityCode = 0;
    }

    uint32_t cityCode;
    WiFiClient wifiClient;
    HTTPClient httpClient;
    static CityWeather *instance;
public:
    DisplayInfo info;

    static CityWeather *getInstance();

    //获取天气信息
    ErrorStatus getCityWeater();
private:
    //json解析
    ErrorStatus parseJson(String &jsonStr);

    ErrorStatus parseDisplayInfo(String &dz, String &sk, String &fc);

    //获取城市代码
    ErrorStatus getCityCode();
};


#endif //WEATHERCLOCK_CITYWEATHER_H
