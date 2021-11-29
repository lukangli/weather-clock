//
// Created by lukang on 2021/11/28.
//

#include "WebConfig.h"
#include "Arduino.h"

WebConfig *WebConfig::getInstance()
{
    if (instance == nullptr) {
        instance = new WebConfig;
    }
    return instance;
}

void WebConfig::webConfigInit()
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

    delay(3000);
    wiFiManager.resetSettings(); // wipe settings

    const char* set_rotation = "<br/><label for='set_rotation'>Set Rotation</label>\
                              <input type='radio' name='set_rotation' value='0' checked> One<br>\
                              <input type='radio' name='set_rotation' value='1'> Two<br>\
                              <input type='radio' name='set_rotation' value='2'> Three<br>\
                              <input type='radio' name='set_rotation' value='3'> Four<br>";
    WiFiManagerParameter  custom_rot(set_rotation); // custom html input
    WiFiManagerParameter  custom_bl("LCDBL","LCD BackLight(1-100)","10",3);
    WiFiManagerParameter  custom_cc("CityCode","CityCode","101250101",9);
    WiFiManagerParameter  p_lineBreak_notext("<p></p>");

    wiFiManager.addParameter(&p_lineBreak_notext);
    wiFiManager.addParameter(&custom_cc);
    wiFiManager.addParameter(&p_lineBreak_notext);
    wiFiManager.addParameter(&custom_bl);
    wiFiManager.addParameter(&p_lineBreak_notext);
    wiFiManager.addParameter(&custom_rot);
    wiFiManager.setSaveConfigCallback(saveParamCallback);
    wiFiManager.setMinimumSignalQuality(20);  // set min RSSI (percentage) to show in scans, null = 8%

    if (!wiFiManager.autoConnect("AutoConnectAP")) {
        Serial.println("配网失败，请重试");
    }

}

void WebConfig::saveParamCallback() {

}

//void Webconfig()
//{

//}
