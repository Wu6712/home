#ifndef __FAN_H__
#define __FAN_H__

#include <analogWrite.h>
#define fanPin1 19
#define fanPin2 18
int speed_val = 0; //定义速度的变量

void fanInit()
{
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
}


void changeFanGear(int gear)
{
  switch(gear)
  {
    case 0: speed_val = 0; Serial.println(speed_val);break;  //调速
    case 1: speed_val = 130; Serial.println(speed_val);break;
    case 2: speed_val = 180; Serial.println(speed_val);break;
    case 3: speed_val = 230; Serial.println(speed_val);break;
  }

  digitalWrite(fanPin1, LOW);
  analogWrite(fanPin2, speed_val);

}

String readFanGear()
{
  return String(speed_val);
}

#endif