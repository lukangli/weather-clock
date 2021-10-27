//
// Created by lukang on 2021/10/27.
//

#ifndef WEATHERCLOCK_CITYWEATHER_H
#define WEATHERCLOCK_CITYWEATHER_H
#include <ESP8266HTTPClient.h>

typedef enum {
    FAILED = 0,
    SUCCESS
} ErrorStatus;

class CityWeather {
private:
    CityWeather() = default;

    WiFiClient wifiClient;
    HTTPClient httpClient;
    uint32_t  cityCode;
    static CityWeather* instance;
public:
    static CityWeather* getInstance();
    ErrorStatus getCityCode();
};


#endif //WEATHERCLOCK_CITYWEATHER_H
