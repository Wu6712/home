#ifndef __GAS_H__
#define __GAS_H__

#define gasPin 23

void gasInit()
{
  pinMode(gasPin, INPUT);
}

// 1,安全;0,危险
String getGasValue()
{
  return String(digitalRead(gasPin));
}

#endif