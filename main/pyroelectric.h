#ifndef __PYROELECTRIC_H__
#define __PYROELECTRIC_H__

#define pyroelectric 14

void pyroelectricInit()
{
  pinMode(pyroelectric, INPUT);
}

// 1,有人;0,没人
String getPyroelectricValue()
{
  return String(digitalRead(pyroelectric));
}

#endif