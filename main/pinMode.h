#ifndef __PINMODE_H__
#define __PINMODE_H__

#define led_y 12

void pinInit()
{
  pinMode(led_y, OUTPUT);
}

void pinOn()
{
  digitalWrite(led_y, HIGH);
}

void pinOff()
{
  digitalWrite(led_y, LOW);
}

#endif