#ifndef __WATER_DROP__
#define __WATER_DROP__

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