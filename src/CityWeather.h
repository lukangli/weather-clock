//
// Created by lukang on 2021/10/27.
//

#ifndef WEATHERCLOCK_CITYWEATHER_H
#define WEATHERCLOCK_CITYWEATHER_H

#include <ESP8266HTTPClient.h>

#define BUFFER_SIZE 512
typedef struct displayInfo
{
    int tempNum = 0;   //温度百分比
    int humidityNum = 0;   //湿度百分比
    int tempCol = 0xffff;   //温度显示颜色
    int humidityCol = 0xffff;   //湿度显示颜色
    int weatherCode = 0;
    uint16_t pm25Num = 0;
    uint32_t pm25BgColor = 0;
    int32_t weatherIcon = 0;
    String cityName;
    String aqi;
    String scrollText[7]; //滚动显示

    String tostring() const
    {
        char buffer[BUFFER_SIZE];
        sprintf(buffer,
                "tempNum = %d, humidityNum = %d, tempCol = %d, humidityCol = %d, cityName = %s, aqi = %s, pm25Num = %d,"
                " pm25BgColor = %d, weatherIcon = %d", tempNum, humidityNum, tempCol, humidityCol, cityName.c_str(),
                aqi.c_str(), pm25Num, pm25BgColor, weatherIcon);
        String str(buffer);
        return str;
    }
} DisplayInfo;

typedef enum
{
    FAILED = 0,
    SUCCESS
} ErrorStatus;

class CityWeather
{
private:
    CityWeather()
    {
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
    ErrorStatus getCityWeather();

private:
    //json解析
    ErrorStatus parseJson(String &jsonStr);

    ErrorStatus parseDisplayInfo(String &dz, String &sk, String &fc);

    //获取城市代码
    ErrorStatus getCityCode();
};


#endif //WEATHERCLOCK_CITYWEATHER_H
