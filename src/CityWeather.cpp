//
// Created by lukang on 2021/10/27.
//

#include "CityWeather.h"
#include <Arduino.h>
#include <TimeLib.h>

#define USERAGENT "Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) " \
    "AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1"
#define URLWGEO "http://wgeo.weather.com.cn/ip/?_="
#define URL "http://www.weather.com.cn/"

CityWeather *CityWeather::getInstance() {
    if (instance == nullptr) {
        instance = new CityWeather;
    }
    return instance;
}

// 发送HTTP请求并且将服务器响应通过串口输出
ErrorStatus CityWeather::getCityCode()
{
    String url = URLWGEO + String(now());

    httpClient.begin(wifiClient, url);

    //设置请求头中的User-Agent
    httpClient.setUserAgent(USERAGENT);
    httpClient.addHeader("Referer", URL);

    //启动连接并发送HTTP请求
    int httpCode = httpClient.GET();
    Serial.print("Send GET request to URL: ");
    Serial.println(url);

    //如果服务器响应OK则从服务器获取响应体信息并通过串口输出
    if (httpCode == HTTP_CODE_OK) {
        String str = httpClient.getString();
        int index = str.indexOf("id=");
        if (index > -1) {
            cityCode = str.substring(index + 4,index + 4 + 9).toInt();
            Serial.println(cityCode);
        } else {
            return FAILED;
        }
    } else {
        Serial.println(httpCode);
        return FAILED;
    }

    //关闭ESP8266与服务器连接
    httpClient.end();
    return SUCCESS;
}