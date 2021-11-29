//
// Created by lukang on 2021/10/27.
//

#include "TftDisplay.h"
#include "humidity.h"
#include "temperature.h"
#include "ArduinoJson.h"
#include "EepromUtils.h"
#include "font/ZdyLwFont_20.h"

TftDisplay::TftDisplay()
{
    //设置背光引脚为输出模式
    pinMode(LCD_BL_PIN, OUTPUT);
    //输出PWM信号设置背光
    analogWrite(LCD_BL_PIN, 1023 - (EepromUtils::getBacklight() * 10));

    /* TFT init */
    tft.begin();
    //反转所有显示颜色：true反转，false正常
    tft.invertDisplay(true);
    tft.setRotation(EepromUtils::getScreenOrient());
    tft.fillScreen(0x0000);
    tft.setTextColor(TFT_BLACK, bgColor);

    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(tft_output);
}

TftDisplay *TftDisplay::getInstance()
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
    clk.drawRoundRect(0, 0, 200, 16, 8, 0xFFFF);  //空心圆角矩形
    clk.fillRoundRect(3, 3, loadNum++, 10, 5, 0xFFFF);  //实心圆角矩形
    clk.setTextDatum(CC_DATUM);   //设置文本数据
    clk.setTextColor(TFT_GREEN, 0x0000);
    clk.drawString("Connecting to WiFi......", 100, 40, 2);
    clk.setTextColor(TFT_WHITE, 0x0000);
    clk.drawRightString(VERSION, 180, 60, 2);
    clk.pushSprite(20, 120);  //窗口位置
    clk.deleteSprite();
    delay(delayTime);

    return loadNum;
}

//TFT屏幕输出函数
bool TftDisplay::tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    if (y >= getInstance()->tft.height())
        return false;
    getInstance()->tft.pushImage(x, y, w, h, bitmap);
    return true;
}

void TftDisplay::displayTempHumidity()
{
    tft.fillScreen(TFT_BLACK); //清屏

    TJpgDec.drawJpg(15, 183, temperature, sizeof(temperature));  //温度图标
    TJpgDec.drawJpg(15, 213, humidity, sizeof(humidity));  //湿度图标
}

void TftDisplay::printfWeather(int num)
{
    switch (num) {
        case 00:
            TJpgDec.drawJpg(170, 15, t0, sizeof(t0));
            break;
        case 01:
            TJpgDec.drawJpg(170, 15, t2, sizeof(t2));
            break;
        case 03:
            TJpgDec.drawJpg(170, 15, t3, sizeof(t3));
            break;
        case 04:
            TJpgDec.drawJpg(170, 15, t4, sizeof(t4));
            break;
        case 05:
            TJpgDec.drawJpg(170, 15, t5, sizeof(t5));
            break;
        case 06:
            TJpgDec.drawJpg(170, 15, t6, sizeof(t6));
            break;
        case 07:
        case 8:
        case 21:
        case 22:
            TJpgDec.drawJpg(170, 15, t7, sizeof(t7));
            break;
        case 9:
        case 10:
        case 23:
        case 24:
            TJpgDec.drawJpg(170, 15, t9, sizeof(t9));
            break;
        case 11:
        case 12:
        case 25:
        case 301:
            TJpgDec.drawJpg(170, 15, t11, sizeof(t11));
            break;
        case 13:
            TJpgDec.drawJpg(170, 15, t13, sizeof(t13));
            break;
        case 14:
        case 26:
            TJpgDec.drawJpg(170, 15, t14, sizeof(t14));
            break;
        case 15:
        case 27:
            TJpgDec.drawJpg(170, 15, t15, sizeof(t15));
            break;
        case 16:
        case 17:
        case 28:
        case 302:
            TJpgDec.drawJpg(170, 15, t16, sizeof(t16));
            break;
        case 18:
            TJpgDec.drawJpg(170, 15, t18, sizeof(t18));
        case 19:
            TJpgDec.drawJpg(170, 15, t19, sizeof(t19));
            break;
        case 20:
            TJpgDec.drawJpg(170, 15, t20, sizeof(t20));
            break;
        case 29:
            TJpgDec.drawJpg(170, 15, t29, sizeof(t29));
            break;
        case 30:
            TJpgDec.drawJpg(170, 15, t30, sizeof(t30));
            break;
        case 31:
            TJpgDec.drawJpg(170, 15, t31, sizeof(t31));
            break;
        case 53:
        case 32:
        case 49:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
            TJpgDec.drawJpg(170, 15, t53, sizeof(t53));
            break;
        default:
            TJpgDec.drawJpg(170, 15, t99, sizeof(t99));
    }
}

void TftDisplay::printfW3660(int x, int y, int num)
{
    switch (num) {
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
    switch (num) {
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
    switch (num) {
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

void TftDisplay::displaySpaceman()
{
    int x = 160, y = 160;

    if (millis() - AprevTime > 37) {
        Anim++;
        AprevTime = millis();
    }

    if (Anim == 10) {
        Anim = 0;
    }

    switch (Anim) {
        case 0:
            TJpgDec.drawJpg(x, y, i0, sizeof(i0));
            break;
        case 1:
            TJpgDec.drawJpg(x, y, i1, sizeof(i1));
            break;
        case 2:
            TJpgDec.drawJpg(x, y, i2, sizeof(i2));
            break;
        case 3:
            TJpgDec.drawJpg(x, y, i3, sizeof(i3));
            break;
        case 4:
            TJpgDec.drawJpg(x, y, i4, sizeof(i4));
            break;
        case 5:
            TJpgDec.drawJpg(x, y, i5, sizeof(i5));
            break;
        case 6:
            TJpgDec.drawJpg(x, y, i6, sizeof(i6));
            break;
        case 7:
            TJpgDec.drawJpg(x, y, i7, sizeof(i7));
            break;
        case 8:
            TJpgDec.drawJpg(x, y, i8, sizeof(i8));
            break;
        case 9:
            TJpgDec.drawJpg(x, y, i9, sizeof(i9));
            break;
        default:
            Serial.println("显示Anim错误");
            break;
    }
}

void TftDisplay::displayWeather()
{
    //获取天气信息
    if (!CityWeather::getInstance()->getCityWeather()) {
        return;
    }

    displayTempHumidity();

    DisplayInfo *info = &CityWeather::getInstance()->info;

    /***绘制相关文字***/
    clk.setColorDepth(8);
    clk.loadFont(ZdyLwFont_20);

    //温度
    humidityTempNum(String(info->tempNum) + "℃", 100, 184);
    humidityTempProgressBar(info->tempNum, info->tempCol, 45, 192);
    //湿度
    humidityTempNum(String(info->humidityNum) + "%", 100, 214);
    humidityTempProgressBar(info->humidityNum, info->humidityCol, 45, 222);

    //城市名称
    clk.createSprite(94, 30);
    clk.fillSprite(bgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_WHITE, bgColor);
    clk.drawString(info->cityName, 44, 16);
    clk.pushSprite(15, 15);
    clk.deleteSprite();

    //PM2.5空气指数
    clk.createSprite(56, 24);
    clk.fillSprite(bgColor);
    info->pm25BgColor = tft.color24to16(info->pm25BgColor);
    clk.fillRoundRect(0, 0, 50, 24, 4, info->pm25BgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(0x0000);
    clk.drawString(info->aqi, 25, 13);
    clk.pushSprite(104, 18);
    clk.deleteSprite();

    //天气图标
    printfWeather(info->weatherIcon);

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
    clk.drawRoundRect(0, 0, 52, 6, 3, 0xFFFF);
    //实心圆角矩形
    clk.fillRoundRect(1, 1, num, 4, 2, col);
    //窗口位置
    clk.pushSprite(x, y);
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
    clk.drawString(str, 28, 13);
    clk.pushSprite(x, y);
    clk.deleteSprite();
}

void TftDisplay::scrollBanner()
{
    DisplayInfo *info = &CityWeather::getInstance()->info;
    if (info->scrollText[currentIndex]) {
        clk.setColorDepth(8);
        clk.loadFont(ZdyLwFont_20);
        clk.createSprite(150, 30);
        clk.fillSprite(TftDisplay::getInstance()->bgColor);
        clk.setTextWrap(false);
        clk.setTextDatum(CC_DATUM);
        clk.setTextColor(TFT_WHITE, TftDisplay::getInstance()->bgColor);
        clk.drawString(info->scrollText[currentIndex], 74, 16);
        clk.pushSprite(10, 45);
        clk.deleteSprite();
        clk.unloadFont();
        if (currentIndex >= 5)
            currentIndex = 0;  //回第一个
        else
            currentIndex += 1;  //准备切换到下一个
    }
}

void TftDisplay::displayDigitalClock()
{
    int timey = 82;
    //时钟刷新
    if (hour() != Hour_sign) {
        printfW3660(20, timey, hour() / 10);
        printfW3660(60, timey, hour() % 10);
        Hour_sign = hour();
    }
    //分钟刷新
    if (minute() != Minute_sign) {
        printfO3660(101, timey, minute() / 10);
        printfO3660(141, timey, minute() % 10);
        Minute_sign = minute();
    }
    //秒钟刷新
    if (second() != Second_sign) {
        printfW1830(182, timey + 30, second() / 10);
        printfW1830(202, timey + 30, second() % 10);
        Second_sign = second();
    }

    /***日期****/
    clk.setColorDepth(8);
    clk.loadFont(ZdyLwFont_20);

    //星期
    clk.createSprite(58, 30);
    clk.fillSprite(bgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_WHITE, bgColor);
    clk.drawString(TimeUtils::getWeek(), 29, 16);
    clk.pushSprite(102, 150);
    clk.deleteSprite();

    //月日
    clk.createSprite(95, 30);
    clk.fillSprite(bgColor);
    clk.setTextDatum(CC_DATUM);
    clk.setTextColor(TFT_WHITE, bgColor);
    clk.drawString(TimeUtils::getMonthDay(), 49, 16);
    clk.pushSprite(5, 150);
    clk.deleteSprite();

    clk.unloadFont();
}

void TftDisplay::displayWebConfig()
{
    clk.setColorDepth(8);

    clk.createSprite(200, 60);//创建窗口
    clk.fillSprite(0x0000);   //填充率

    clk.setTextDatum(CC_DATUM);   //设置文本数据
    clk.setTextColor(TFT_GREEN, 0x0000);
    clk.drawString("WiFi Connect Fail!",100,10,2);
    clk.drawString("SSID:",45,40,2);
    clk.setTextColor(TFT_WHITE, 0x0000);
    clk.drawString("AutoConnectAP",125,40,2);
    clk.pushSprite(20,50);  //窗口位置

    clk.deleteSprite();
}
