#ifndef SERVOS_H
#define SERVOS_H

#include <ESP32_Servo.h>
Servo myservo; // 创建舵机对象来控制舵机

int pos = 0; // 建立变量来存储伺服位置

int doorServoPin = 13;
int windowServoPin = 5;



void windowServosInit()
{
  myservo.attach(servoPin);
}

void windowOpen()
{
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
}

void windowClose()
{
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }

}


#endif