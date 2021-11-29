//
// Created by lukang on 2021/11/28.
//

#ifndef WEATHERCLOCK_EEPROMUTILS_H
#define WEATHERCLOCK_EEPROMUTILS_H
#include "Arduino.h"

class EepromUtils {
private:
    EepromUtils();

    static EepromUtils *instance;
public:
    //单例模式
    static EepromUtils *getInstance();

    //获取背光值
    static uint8_t getBacklight();

    //获取屏幕方向值
    static uint8_t getScreenOrient();

    //设置背光值
    static void setBacklight(uint8_t backlightPwm);

    //设置屏幕方向值
    static void setScreenOrient(uint8_t screenOrient);
};


#endif //WEATHERCLOCK_EEPROMUTILS_H
