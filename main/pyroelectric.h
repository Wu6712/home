#ifndef PYROELECTRIC_H
#define PYROELECTRIC_H

#define pyroelectric 14

void pyroelectricInit()
{
  pinMode(pyroelectric, INPUT);
}

boolean getPyroelectricValue()
{
  boolean pyroelectric_val = digitalRead(pyroelectric);
  return pyroelectric_val;
}

#endif