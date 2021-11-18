//
// Created by lukang on 2021/11/6.
//

#ifndef WEATHERCLOCK_TIMEUTIL_H
#define WEATHERCLOCK_TIMEUTIL_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>

class TimeUtil
{
    static WiFiUDP *wifiUdp;
    static TimeUtil *instance;

    TimeUtil();

    ~TimeUtil();
public:

    static TimeUtil *getInstance();

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


#endif //WEATHERCLOCK_TIMEUTIL_H
