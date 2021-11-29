//
// Created by lukang on 2021/11/28.
//

#ifndef WEATHERCLOCK_WEBCONFIG_H
#define WEATHERCLOCK_WEBCONFIG_H
#include <WiFiManager.h>

class WebConfig {
private:
    WebConfig() = default;

    static WebConfig *instance;

    WiFiManager wiFiManager;
public:
    //单例模式
    static WebConfig *getInstance();

    void webConfigInit();

    static void saveParamCallback();
};


#endif //WEATHERCLOCK_WEBCONFIG_H
