#ifndef __LCD_H__
#define __LCD_H__

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);

void lcdInit()
{
  mylcd.init();
  mylcd.backlight();
}

void showHello() {
  mylcd.setCursor(0, 0);
  mylcd.print("hello");
  mylcd.setCursor(0, 1);
  mylcd.print("keyes");
  //mylcd.clear();
}

#endif