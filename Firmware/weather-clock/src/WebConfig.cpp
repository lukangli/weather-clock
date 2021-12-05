//
// Created by lukang on 2021/11/28.
//

#include "WebConfig.h"
#include "Arduino.h"
#include "TftDisplay.h"

WebConfig *WebConfig::getInstance()
{
    if (instance == nullptr) {
        instance = new WebConfig;
    }
    return instance;
}

void WebConfig::webConfigInit()
{
    wiFiManager.setSaveConfigCallback(saveParamCallback);
    wiFiManager.setMinimumSignalQuality(20);  // set min RSSI (percentage) to show in scans, null = 8%
    wiFiManager.setConnectTimeout(10);
    wiFiManager.setTimeout(15);

    if (!wiFiManager.autoConnect("helloWorld")) {
        Serial.println("配网失败，请重试");
    }
}

void WebConfig::saveParamCallback()
{
    Serial.println(WebConfig::getInstance()->wiFiManager.getConfigPortalSSID());
    String value;
}