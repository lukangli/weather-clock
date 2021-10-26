#include <Arduino.h>
#include <TFT_eSPI.h>
#include "TJpg_Decoder.h"

//LCD屏幕相关设置
TFT_eSPI tft = TFT_eSPI();  // 引脚请自行配置tft_espi库中的 User_Setup.h文件
TFT_eSprite clk = TFT_eSprite(&tft);
#define LCD_BL_PIN 5    //LCD背光引脚
uint16_t bgColor = 0x0000;

int LCD_Rotation = 0;   //LCD屏幕方向
int LCD_BL_PWM = 100;//屏幕亮度0-100，默认50

void setup() {
    Serial.begin(115200);
    pinMode(LCD_BL_PIN, OUTPUT);
    analogWrite(LCD_BL_PIN, 1023 - (LCD_BL_PWM * 10));
    tft.begin(); /* TFT init */
    tft.invertDisplay(0);
    tft.setRotation(LCD_Rotation);
    tft.fillScreen(0);
    tft.setTextColor(TFT_BLACK, bgColor);

    clk.setColorDepth(8);

    clk.createSprite(200, 100);//创建窗口
    clk.fillSprite(0x0000);   //填充率

    clk.drawRoundRect(0,0,200,16,8,0xFFFF);       //空心圆角矩形
    clk.fillRoundRect(3,3,2,10,5,0xFFFF);   //实心圆角矩形
    clk.setTextDatum(CC_DATUM);   //设置文本数据
    clk.setTextColor(TFT_GREEN, 0x0000);
    clk.drawString("Connecting to WiFi......",100,40,2);
    clk.setTextColor(TFT_WHITE, 0x0000);
    clk.drawRightString("lukang",180,60,2);
    clk.pushSprite(20,120);  //窗口位置
}

void loop() {
    delay(2000);
    Serial.println("clion hello!");
}