//
// Created by lukang on 2021/11/6.
//

#include "TimeUtil.h"

#define TIME_ZONE 8  // 东八区
#define NTP_PACKET_SIZE 48

static const char ntpServerName[] = "ntp6.aliyun.com";

TimeUtil::TimeUtil()
{
    wifiUdp = new WiFiUDP;
    //开启UDP传输
    wifiUdp->begin(8000);
    //设置时间解析回调函数
    setSyncProvider(getNtpTime);
    //设置同步时间间隔
    setSyncInterval(300);
}

TimeUtil::~TimeUtil()
{
    delete wifiUdp;
}

TimeUtil *TimeUtil::getInstance()
{
    if (instance == nullptr) {
        instance = new TimeUtil;
    }
    return instance;
}

time_t TimeUtil::getNtpTime()
{
    IPAddress ntpServerIP; // NTP server's ip address

    while (wifiUdp->parsePacket() > 0); // discard any previously received packets

    WiFi.hostByName(ntpServerName, ntpServerIP);

    byte* buffer = sendNTPRequest(ntpServerIP);

    uint32_t beginWait = millis();

    while (millis() - beginWait < 1500) {

        int size = wifiUdp->parsePacket();
        if (size >= NTP_PACKET_SIZE) {
            Serial.println("Receive NTP Response");
            wifiUdp->read(buffer, NTP_PACKET_SIZE);
            unsigned long secsSince1900;
            secsSince1900 =  (unsigned long) buffer[40] << 24;
            secsSince1900 |= (unsigned long) buffer[41] << 16;
            secsSince1900 |= (unsigned long) buffer[42] << 8;
            secsSince1900 |= (unsigned long) buffer[43];
            delete [] buffer;
            return secsSince1900 - 2208988800UL + TIME_ZONE * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    delete [] buffer;
    return 0; // 无法获取时间时返回0
}

// 向NTP服务器发送请求
byte* TimeUtil::sendNTPRequest(IPAddress &address)
{
    byte *buffer = new byte[NTP_PACKET_SIZE];

    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    buffer[0] = 0b11100011;   // LI, Version, Mode
    buffer[1] = 0;     // Stratum, or type of clock
    buffer[2] = 6;     // Polling Interval
    buffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    buffer[12] = 49;
    buffer[13] = 0x4E;
    buffer[14] = 49;
    buffer[15] = 52;
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    wifiUdp->beginPacket(address, 123); //NTP requests are to port 123
    wifiUdp->write(buffer, NTP_PACKET_SIZE);
    wifiUdp->endPacket();

    return buffer;
}

String TimeUtil::getWeek()
{
    String weekList[7] = {"日", "一", "二", "三", "四", "五", "六"};
    String week = "周" + weekList[weekday() - 1];
    return week;
}

String TimeUtil::getMonthDay()
{
    String monthDay = String(month());
    monthDay = monthDay + "月" + String(day()) + "日";
    return monthDay;
}
