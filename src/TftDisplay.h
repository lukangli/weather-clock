//
// Created by lukang on 2021/10/27.
//

#ifndef WEATHERCLOCK_TFTDISPLAY_H
#define WEATHERCLOCK_TFTDISPLAY_H
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include "CityWeather.h"

#include "font/O_3660_i0.h"
#include "font/O_3660_i1.h"
#include "font/O_3660_i2.h"
#include "font/O_3660_i3.h"
#include "font/O_3660_i4.h"
#include "font/O_3660_i5.h"
#include "font/O_3660_i6.h"
#include "font/O_3660_i7.h"
#include "font/O_3660_i8.h"
#include "font/O_3660_i9.h"

#include "font/W_3660_i0.h"
#include "font/W_3660_i1.h"
#include "font/W_3660_i2.h"
#include "font/W_3660_i3.h"
#include "font/W_3660_i4.h"
#include "font/W_3660_i5.h"
#include "font/W_3660_i6.h"
#include "font/W_3660_i7.h"
#include "font/W_3660_i8.h"
#include "font/W_3660_i9.h"

#include "font/W_1830_i0.h"
#include "font/W_1830_i1.h"
#include "font/W_1830_i2.h"
#include "font/W_1830_i3.h"
#include "font/W_1830_i4.h"
#include "font/W_1830_i5.h"
#include "font/W_1830_i6.h"
#include "font/W_1830_i7.h"
#include "font/W_1830_i8.h"
#include "font/W_1830_i9.h"

#include "img/tianqi/t0.h"
#include "img/tianqi/t1.h"
#include "img/tianqi/t2.h"
#include "img/tianqi/t3.h"
#include "img/tianqi/t4.h"
#include "img/tianqi/t5.h"
#include "img/tianqi/t6.h"
#include "img/tianqi/t7.h"
#include "img/tianqi/t9.h"
#include "img/tianqi/t11.h"
#include "img/tianqi/t13.h"
#include "img/tianqi/t14.h"
#include "img/tianqi/t15.h"
#include "img/tianqi/t16.h"
#include "img/tianqi/t18.h"
#include "img/tianqi/t19.h"
#include "img/tianqi/t20.h"
#include "img/tianqi/t26.h"
#include "img/tianqi/t29.h"
#include "img/tianqi/t30.h"
#include "img/tianqi/t31.h"
#include "img/tianqi/t53.h"
#include "img/tianqi/t99.h"

#define LCD_BL_PIN 5    //LCD背光引脚
#define VERSION   "V1.4"

class TftDisplay {
private:
    uint8_t lcdRotation = 0;   //LCD屏幕方向
    uint8_t lcdBlPwm = 100;//屏幕亮度0-100，默认50
    uint16_t bgColor = 0x0000;

    static TftDisplay* instance;

    TftDisplay();
public:
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSprite clk = TFT_eSprite(&tft);

    //单例模式
    static TftDisplay* getInstance();

    //进度条加载
    uint16 loading(byte delayTime);

    //显示温湿度图标
    void displayTempHumidity();

    //图片显示回调函数
    static bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap);

    //显示天气图标
    void printfWeather(int x, int y, int num);

    //显示白色36*60大小数字
    void printfW3660(int x,int y,int num);

    //显示橙色36*60大小数字
    void printfO3660(int x,int y,int num);

    //显示白色18*30大小数字
    void printfW1830(int x,int y,int num);

    //显示天气到屏幕
    void displayWeather();

private:
    //显示温湿度到屏幕(进度条方式)
    void humidityTempProgressBar(int32_t num, int32_t col, int32_t x, int32_t y);

    //显示温湿度到屏幕(数字方式)
    void humidityTempNum(const String &str, int32_t x, int32_t y);
};

#endif //WEATHERCLOCK_TFTDISPLAY_H
