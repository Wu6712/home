#ifndef __FAN_H__
#define __FAN_H__

#define fanPin1 19
#define fanPin2 18

void fanInit()
{
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
}




#endif