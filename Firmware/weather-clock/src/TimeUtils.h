//
// Created by lukang on 2021/11/6.
//

#ifndef WEATHERCLOCK_TIMEUTILS_H
#define WEATHERCLOCK_TIMEUTILS_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>

class TimeUtils
{
    static WiFiUDP *wifiUdp;
    static TimeUtils *instance;

    TimeUtils();

    ~TimeUtils();
public:

    static TimeUtils *getInstance();

    //获取周
    static String getWeek();

    //获取月信息
    static String getMonthDay();
private:
    //NTP时间获取
    static time_t getNtpTime();

    //向NTP服务器发送请求
    static byte* sendNTPRequest(IPAddress &address);
};


#endif //WEATHERCLOCK_TIMEUTILS_H
