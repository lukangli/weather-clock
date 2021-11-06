//
// Created by lukang on 2021/10/27.
//

#include "CityWeather.h"
#include <Arduino.h>
#include <TimeLib.h>
#include <ArduinoJson.h>

#define USERAGENT "Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) " \
    "AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1"
#define URL_WEATHER "http://wgeo.weather.com.cn/ip/?_="
#define URL "http://www.weather.com.cn/"
#define URL_D1 "http://d1.weather.com.cn/weather_index/"

CityWeather *CityWeather::getInstance()
{
    if (instance == nullptr) {
        instance = new CityWeather;
    }
    return instance;
}

// 发送HTTP请求并且将服务器响应通过串口输出
ErrorStatus CityWeather::getCityCode()
{
    String url = URL_WEATHER + String(now());

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
            cityCode = str.substring(index + 4, index + 4 + 9).toInt();
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

// 获取城市天气
ErrorStatus CityWeather::getCityWeather()
{
    if (!getCityCode()) {
        Serial.println("获取城市代号失败");
        return FAILED;
    }

    if (!cityCode) {
        Serial.println("请先获取城市代号");
        return FAILED;
    }

    String url = URL_D1 + String(cityCode) + ".html?_=" + String(now());

    httpClient.begin(wifiClient, url);

    httpClient.setUserAgent(USERAGENT);
    httpClient.addHeader("Referer", URL);

    int httpCode = httpClient.GET();
    Serial.println("正在获取天气数据");
    Serial.println(url);

    //如果服务器响应OK则从服务器获取响应体信息并通过串口输出
    if (httpCode == HTTP_CODE_OK) {

        String str = httpClient.getString();
        if (!parseJson(str)) {
            return FAILED;
        }
    } else {
        Serial.println("请求城市天气错误：");
        Serial.print(httpCode);
        httpClient.end();
        return FAILED;
    }
    Serial.println("获取天气数据成功");
    //关闭ESP8266与服务器连接
    httpClient.end();
    return SUCCESS;
}

/**
 *
 * @param str 网站返回的天气信息
 * @return
 */
ErrorStatus CityWeather::parseJson(String &str)
{

    if (str.isEmpty()) {
        Serial.println("parseJson str is empty");
        return FAILED;
    }

    int indexStart = str.indexOf("weatherinfo\":");
    int indexEnd = str.indexOf("};var alarmDZ");
    if (indexStart < 0 || indexEnd < 0) {
        Serial.println("weather info is error");
        return FAILED;
    }

    String jsonCityDZ = str.substring(indexStart + 13, indexEnd);

    indexStart = str.indexOf("dataSK =");
    indexEnd = str.indexOf(";var dataZS");
    if (indexStart < 0 || indexEnd < 0) {
        Serial.println("dataSK is error");
        return FAILED;
    }

    String jsonDataSK = str.substring(indexStart + 8, indexEnd);

    indexStart = str.indexOf("\"f\":[");
    indexEnd = str.indexOf(",{\"fa");
    if (indexStart < 0 || indexEnd < 0) {
        Serial.println("fa is error");
        return FAILED;
    }

    String jsonFC = str.substring(indexStart + 5, indexEnd);

    if (!parseDisplayInfo(jsonCityDZ, jsonDataSK, jsonFC)) {
        Serial.println("显示信息解析错误");
        return FAILED;
    }
    return SUCCESS;
}

ErrorStatus CityWeather::parseDisplayInfo(String &dzJson, String &skJson, String &fcJson)
{
    if (dzJson.isEmpty() || dzJson.isEmpty() || dzJson.isEmpty()) {
        return FAILED;
    }

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, skJson);
    JsonObject sk = doc.as<JsonObject>();

    info.tempNum = sk["temp"].as<int>();
    if (info.tempNum < 10)
        info.tempCol = 0x00FF;
    else if (info.tempNum < 28)
        info.tempCol = 0x0AFF;
    else if (info.tempNum < 34)
        info.tempCol = 0x0F0F;
    else if (info.tempNum < 41)
        info.tempCol = 0xFF0F;
    else if (info.tempNum < 49)
        info.tempCol = 0xF00F;
    else {
        info.tempCol = 0xF00F;
        info.tempNum = 50;
    }

    info.humidityNum = (sk["SD"].as<String>()).substring(0, 2).toInt();
    if (info.humidityNum > 90)
        info.humidityCol = 0x00FF;
    else if (info.humidityNum > 70)
        info.humidityCol = 0x0AFF;
    else if (info.humidityNum > 40)
        info.humidityCol = 0x0F0F;
    else if (info.humidityNum > 20)
        info.humidityCol = 0xFF0F;
    else
        info.humidityCol = 0xF00F;

    info.pm25BgColor = 0x880b20;//优
    info.pm25Num = sk["aqi"];
    if (info.pm25Num > 200) {
        info.pm25BgColor = 0x880b20;//重度 0x880b20
        info.aqi = "重度";
    } else if (info.pm25Num > 150) {
        info.pm25BgColor = 0xba3779;//中度 0xba3779
        info.aqi = "中度";
    } else if (info.pm25Num > 100) {
        info.pm25BgColor = 0xf29f39;//轻 0xf29f39
        info.aqi = "轻度";
    } else if (info.pm25Num > 50) {
        info.pm25BgColor = 0xf7db64;//良 0xf7db64
        info.aqi = "良";
    }

    info.scrollText[0] = "实时天气 " + sk["weather"].as<String>();
    info.scrollText[1] = "空气质量 " + info.aqi;
    info.scrollText[2] = "风向 " + sk["WD"].as<String>() + sk["WS"].as<String>();

    info.cityName = sk["cityname"].as<String>();
    info.weatherIcon = (sk["weathercode"].as<String>()).substring(1, 3).toInt();

    //左上角滚动字幕
    //解析第二段JSON
    deserializeJson(doc, dzJson);
    JsonObject dz = doc.as<JsonObject>();

    info.scrollText[3] = "今日" + dz["weather"].as<String>();

    deserializeJson(doc, fcJson);
    JsonObject fc = doc.as<JsonObject>();

    info.scrollText[4] = "最低温度" + fc["fd"].as<String>() + "℃";
    info.scrollText[5] = "最高温度" + fc["fc"].as<String>() + "℃";

    return SUCCESS;
}