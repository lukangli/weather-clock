//
// Created by lukang on 2021/10/27.
//

#include "TftDisplay.h"
#include "humidity.h"
#include "temperature.h"

TftDisplay::TftDisplay() {
    //设置背光引脚为输出模式
    pinMode(LCD_BL_PIN, OUTPUT);
    //输出PWM信号设置背光
    analogWrite(LCD_BL_PIN, 1023 - (lcdBlPwm * 10));

    /* TFT init */
    tft.begin();
    //反转所有显示颜色：true反转，false正常
    tft.invertDisplay(true);
    tft.setRotation(lcdRotation);
    tft.fillScreen(0x0000);
    tft.setTextColor(TFT_BLACK, bgColor);

    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(tft_output);
}

TftDisplay* TftDisplay::getInstance()
{
    if (instance == nullptr) {
        instance = new TftDisplay();
    }
    return instance;
}

//绘制进度条
uint16_t TftDisplay::loading(byte delayTime)
{
    static uint16_t loadNum = 0;
    clk.setColorDepth(8);
    clk.createSprite(200, 100);//创建窗口
    clk.fillSprite(0x0000);   //填充率
    clk.drawRoundRect(0,0,200,16,8,0xFFFF);  //空心圆角矩形
    clk.fillRoundRect(3,3,loadNum++,10,5,0xFFFF);  //实心圆角矩形
    clk.setTextDatum(CC_DATUM);   //设置文本数据
    clk.setTextColor(TFT_GREEN, 0x0000);
    clk.drawString("Connecting to WiFi......",100,40,2);
    clk.setTextColor(TFT_WHITE, 0x0000);
    clk.drawRightString(VERSION,180,60,2);
    clk.pushSprite(20,120);  //窗口位置
    clk.deleteSprite();
    delay(delayTime);

    return loadNum;
}

//TFT屏幕输出函数
bool TftDisplay::tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    if (y >= getInstance()->tft.height())
        return false;
    getInstance()->tft.pushImage(x, y, w, h, bitmap);
    return true;
}

void TftDisplay::displayTempHumidity() {
    tft.fillScreen(TFT_BLACK);//清屏

    TJpgDec.drawJpg(15,183,temperature, sizeof(temperature));  //温度图标
    TJpgDec.drawJpg(15,213,humidity, sizeof(humidity));  //湿度图标
}
