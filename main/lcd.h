#ifndef LCD_H
#define LCD_H

#define led_y 12

void lcdInit()
{
  pinMode(led_y, OUTPUT);
}

void lcdOn()
{
  digitalWrite(led_y, HIGH);
}

void lcdOff()
{
  digitalWrite(led_y, LOW);
}

#endif