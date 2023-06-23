#ifndef __TEM_HUM__
#define __TEM_HUM__

#include "xht11.h"
xht11 xht(17);

unsigned char dht[4] = {0, 0, 0, 0};

// 读取温度
String readTem()
{
  if (xht.receive(dht)) {
    return String(dht[2]);
  }

  Serial.println("温度读取失败");

}

String readHum()
{
  if (xht.receive(dht)) {
    return String(dht[4]);
  }

  Serial.println("湿度读取失败");
}

#endif