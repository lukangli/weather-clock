//
// Created by lukang on 2021/10/27.
//

#ifndef WEATHERCLOCK_TFTDISPLAY_H
#define WEATHERCLOCK_TFTDISPLAY_H
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>

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
};

#endif //WEATHERCLOCK_TFTDISPLAY_H
