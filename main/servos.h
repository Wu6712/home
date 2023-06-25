#ifndef __SERVOS_H__
#define __SERVOS_H__

#include <ESP32_Servo.h>
Servo doorServo;
Servo windowServo;
#define doorServoPin 13
#define windowServoPin 5

int pos = 0; // 建立变量来存储伺服位置
int initialAngle = 180; // 窗户关闭状态
int currentAngle = 0; // 当前角度


void windowServosInit()
{ 
  windowServo.attach(windowServoPin);
  windowServo.write(0);
}

void doorServosInit()
{
  doorServo.attach(doorServoPin);
  doorServo.write(0);
}


void openTheWindow()
{
  for (pos = 0; pos <= initialAngle; pos += 1) {
    currentAngle = pos;
    windowServo.write(pos);
    delay(15);
  }
}

void closeTheWindow()
{
  for (pos = initialAngle; pos >= 0; pos -= 1) {
    currentAngle = pos;
    windowServo.write(pos);
    delay(15);
  }

}

// 0,关状态;120(>0)开状态
String readWindowState()
{
  return String(windowServo.read());
}

// 门状态
String readDoorState()
{
  return String(doorServo.read());
}

void closeTheDoor()
{
  doorServo.write(0);
}

void openTheDoor()
{
  doorServo.write(180);
}

#endif