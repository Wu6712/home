#ifndef LED_H
#define LED_H

#define led_y 12

// 初始化
void ledInit()
{
  pinMode(led_y, OUTPUT);
}

// 开灯
void ledOn()
{
  digitalWrite(led_y, HIGH);
}

// 关灯
void ledOff()
{
  digitalWrite(led_y, LOW);
}

// 灯状态(1,开状态;0,关状态)
String readLedState()
{
  return String(digitalRead(led_y));
}

#endif