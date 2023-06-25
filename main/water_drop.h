#ifndef __WATER_DROP_H__
#define __WATER_DROP_H__

#define waterPin 34

void initWaterDrop()
{
  pinMode(waterPin, INPUT);
}

String readWaterDropState()
{
  return String(analogRead(waterPin));
}

#endif