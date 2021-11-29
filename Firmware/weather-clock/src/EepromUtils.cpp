//
// Created by lukang on 2021/11/28.
//

#include "EepromUtils.h"
#include "EEPROM.h"

#define BACKLIGHT 1     //被写入数据的EEPROM地址编号  0亮度
#define SCREEN_ORIENT 2 //被写入数据的EEPROM地址编号  2 旋转方向

EepromUtils *EepromUtils::getInstance()
{
    if (instance == nullptr) {
        instance = new EepromUtils;
    }
    return instance;
}

EepromUtils::EepromUtils()
{
    EEPROM.begin(1024);
}

uint8_t EepromUtils::getBacklight()
{
    uint8_t lcdBacklightPWM = EEPROM.read(BACKLIGHT);
    if (lcdBacklightPWM > 0 && lcdBacklightPWM <= 100) {
        return lcdBacklightPWM;
    }

    //等于零返回最大值，否则屏幕不亮
    return 100;
}

uint8_t EepromUtils::getScreenOrient()
{
    uint8_t lcdScreenOrient = EEPROM.read(BACKLIGHT);
    if (lcdScreenOrient <= 3) {
        return lcdScreenOrient;
    }

    return 0;
}

void EepromUtils::setBacklight(uint8_t backlightPwm)
{
    if (EEPROM.read(BACKLIGHT) != backlightPwm) {
        EEPROM.write(BACKLIGHT, backlightPwm);
        if (!EEPROM.commit()) {
            Serial.println("setBacklight eeprom commit error!");
        }
    }
}

void EepromUtils::setScreenOrient(uint8_t screenOrient) {

    if (EEPROM.read(SCREEN_ORIENT) != screenOrient) {
        EEPROM.write(SCREEN_ORIENT, screenOrient);
        if (!EEPROM.commit()) {
            Serial.println("setScreenOrient eeprom commit error!");
        }
    }
}