//
// Created by lukang on 2021/10/27.
//

#include "TftDisplay.h"
#include "humidity.h"
#include "temperature.h"
#include "ArduinoJson.h"
#include "font/ZdyLwFont_20.h"

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
    tft.fillScreen(TFT_BLACK); //清屏

    TJpgDec.drawJpg(15,183,temperature, sizeof(temperature));  //温度图标
    TJpgDec.drawJpg(15,213,humidity, sizeof(humidity));  //湿度图标
}

void TftDisplay::printfWeather(int x, int y, int num)
{
    switch (num) {
        case 00:
            TJpgDec.drawJpg(x, y, t0, sizeof(t0));
            break;
        case 01:
            TJpgDec.drawJpg(x, y, t2, sizeof(t2));
            break;
        case 03:
            TJpgDec.drawJpg(x, y, t3, sizeof(t3));
            break;
        case 04:
            TJpgDec.drawJpg(x, y, t4, sizeof(t4));
            break;
        case 05:
            TJpgDec.drawJpg(x, y, t5, sizeof(t5));
            break;
        case 06:
            TJpgDec.drawJpg(x, y, t6, sizeof(t6));
            break;
        case 07:
        case 8:
        case 21:
        case 22:
            TJpgDec.drawJpg(x, y, t7, sizeof(t7));
            break;
        case 9:
        case 10:
        case 23:
        case 24:
            TJpgDec.drawJpg(x, y, t9, sizeof(t9));
            break;
        case 11:
        case 12:
        case 25:
        case 301:
            TJpgDec.drawJpg(x, y, t11, sizeof(t11));
            break;
        case 13:
            TJpgDec.drawJpg(x, y, t13, sizeof(t13));
            break;
        case 14:
        case 26:
            TJpgDec.drawJpg(x, y, t14, sizeof(t14));
            break;
        case 15:
        case 27:
            TJpgDec.drawJpg(x, y, t15, sizeof(t15));
            break;
        case 16:
        case 17:
        case 28:
        case 302:
            TJpgDec.drawJpg(x, y, t16, sizeof(t16));
            break;
        case 18:
            TJpgDec.drawJpg(x, y, t18, sizeof(t18));
        case 19:
            TJpgDec.drawJpg(x, y, t19, sizeof(t19));
            break;
        case 20:
            TJpgDec.drawJpg(x, y, t20, sizeof(t20));
            break;
        case 29:
            TJpgDec.drawJpg(x, y, t29, sizeof(t29));
            break;
        case 30:
            TJpgDec.drawJpg(x, y, t30, sizeof(t30));
            break;
        case 31:
            TJpgDec.drawJpg(x, y, t31, sizeof(t31));
            break;
        case 53:
        case 32:
        case 49:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
            TJpgDec.drawJpg(x, y, t53, sizeof(t53));
            break;
        default:
            TJpgDec.drawJpg(x, y, t99, sizeof(t99));
    }
}

void TftDisplay::printfW3660(int x, int y, int num)
{
    switch(num)
    {
        case 0:
            TJpgDec.drawJpg(x, y, W_3660_i0, sizeof(W_3660_i0));
            break;
        case 1:
            TJpgDec.drawJpg(x, y, W_3660_i1, sizeof(W_3660_i1));
            break;
        case 2:
            TJpgDec.drawJpg(x, y, W_3660_i2, sizeof(W_3660_i2));
            break;
        case 3:
            TJpgDec.drawJpg(x, y, W_3660_i3, sizeof(W_3660_i3));
            break;
        case 4:
            TJpgDec.drawJpg(x, y, W_3660_i4, sizeof(W_3660_i4));
            break;
        case 5:
            TJpgDec.drawJpg(x, y, W_3660_i5, sizeof(W_3660_i5));
            break;
        case 6:
            TJpgDec.drawJpg(x, y, W_3660_i6, sizeof(W_3660_i6));
            break;
        case 7:
            TJpgDec.drawJpg(x, y, W_3660_i7, sizeof(W_3660_i7));
            break;
        case 8:
            TJpgDec.drawJpg(x, y, W_3660_i8, sizeof(W_3660_i8));
            break;
        case 9:
            TJpgDec.drawJpg(x, y, W_3660_i9, sizeof(W_3660_i9));
            break;
        default:
            Serial.println("显示W_3660数字错误");
            break;
    }
}

void TftDisplay::printfO3660(int x, int y, int num)
{
    switch(num)
    {
        case 0:
            TJpgDec.drawJpg(x, y, O_3660_i0, sizeof(O_3660_i0));
            break;
        case 1:
            TJpgDec.drawJpg(x, y, O_3660_i1, sizeof(O_3660_i1));
            break;
        case 2:
            TJpgDec.drawJpg(x, y, O_3660_i2, sizeof(O_3660_i2));
            break;
        case 3:
            TJpgDec.drawJpg(x, y, O_3660_i3, sizeof(O_3660_i3));
            break;
        case 4:
            TJpgDec.drawJpg(x, y, O_3660_i4, sizeof(O_3660_i4));
            break;
        case 5:
            TJpgDec.drawJpg(x, y, O_3660_i5, sizeof(O_3660_i5));
            break;
        case 6:
            TJpgDec.drawJpg(x, y, O_3660_i6, sizeof(O_3660_i6));
            break;
        case 7:
            TJpgDec.drawJpg(x, y, O_3660_i7, sizeof(O_3660_i7));
            break;
        case 8:
            TJpgDec.drawJpg(x, y, O_3660_i8, sizeof(O_3660_i8));
            break;
        case 9:
            TJpgDec.drawJpg(x, y, O_3660_i9, sizeof(O_3660_i9));
            break;
        default:
            Serial.println("显示O_3660数字错误");
            break;
    }
}

void TftDisplay::printfW1830(int x, int y, int num)
{
    switch(num)
    {
        case 0:
            TJpgDec.drawJpg(x, y, W_1830_i0, sizeof(W_1830_i0));
            break;
        case 1:
            TJpgDec.drawJpg(x, y, W_1830_i1, sizeof(W_1830_i1));
            break;
        case 2:
            TJpgDec.drawJpg(x, y, W_1830_i2, sizeof(W_1830_i2));
            break;
        case 3:
            TJpgDec.drawJpg(x, y, W_1830_i3, sizeof(W_1830_i3));
            break;
        case 4:
            TJpgDec.drawJpg(x, y, W_1830_i4, sizeof(W_1830_i4));
            break;
        case 5:
            TJpgDec.drawJpg(x, y, W_1830_i5, sizeof(W_1830_i5));
            break;
        case 6:
            TJpgDec.drawJpg(x, y, W_1830_i6, sizeof(W_1830_i6));
            break;
        case 7:
            TJpgDec.drawJpg(x, y, W_1830_i7, sizeof(W_1830_i7));
            break;
        case 8:
            TJpgDec.drawJpg(x, y, W_1830_i8, sizeof(W_1830_i8));
            break;
        case 9:
            TJpgDec.drawJpg(x, y, W_1830_i9, sizeof(W_1830_i9));
            break;
        default:
            Serial.println("显示O_1830数字错误");
            break;
    }
}

void TftDisplay::displayWeather()
{
    //获取天气信息
    if (CityWeather::getInstance()->getCityWeater()) {
        return;
    }

    displayTempHumidity();

    DisplayInfo *info = &CityWeather::getInstance()->info;
    /***绘制相关文字***/
    clk.setColorDepth(8);
    clk.loadFont(ZdyLwFont_20);

    //温度
    humidityTempNum(String(info->tempnum) + "℃", 100, 184);
    humidityTempProgressBar(info->tempnum, info->tempcol, 45, 192);
    //湿度
    humidityTempNum(String(info->huminum), 100, 214);
    humidityTempProgressBar(info->huminum, info->humicol, 45, 222);

    //城市名称
    clk.createSprite(94, 30);
    clk.fillSprite(bgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_WHITE, bgColor);
    clk.drawString(info->cityName,44,16);
    clk.pushSprite(15,15);
    clk.deleteSprite();

    //PM2.5空气指数
    clk.createSprite(56, 24);
    clk.fillSprite(bgColor);
    clk.fillRoundRect(0,0,50,24,4,info->pm25BgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(0x0000);
    clk.drawString(info->aqi,25,13);
    clk.pushSprite(104,18);
    clk.deleteSprite();

    //天气图标
    printfWeather(170,15, info->weatherIcon);

    clk.unloadFont();
}

/**
 * 显示进度条
 * @param num
 * @param col
 * @param x  温度：45 ， 湿度：45
 * @param y  温度：192 ，湿度：222
 */
void TftDisplay::humidityTempProgressBar(int32_t num, int32_t col, int32_t x, int32_t y)
{
    clk.setColorDepth(8);

    //创建窗口
    clk.createSprite(52, 6);
    clk.fillSprite(0x0000);    //填充率
    //空心圆角矩形  起始位x,y,长度，宽度，圆弧半径，颜色
    clk.drawRoundRect(0,0,52,6,3,0xFFFF);
    //实心圆角矩形
    clk.fillRoundRect(1,1,num,4,2, col);
    //窗口位置
    clk.pushSprite(x,y);
    clk.deleteSprite();
}

/**
 * 显示数字
 * @param num
 * @param col
 * @param x  温度：100 ，湿度：100
 * @param y  温度：184 ，湿度：214
 */
void TftDisplay::humidityTempNum(const String &str, int32_t x, int32_t y)
{
    clk.createSprite(58, 24);
    clk.fillSprite(bgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_WHITE, bgColor);
    clk.drawString(str,28,13);
    clk.pushSprite(x,y);
    clk.deleteSprite();
}
