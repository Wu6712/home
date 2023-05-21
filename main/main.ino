#include <Wire.h>
#include "wifi_connect.h"
// #include "mqtt_connect.h"
#include "lcd.h"
#include "pyroelectric.h"

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  lcdInit();
  pyroelectricInit();
  // client.setServer(mqtt_server, 1883);
  // client.setCallback(callback);

}


void loop() {
  // mqtt相关操作
  // if (!client.connected()) {
  //   reconnect();
  // }
  // client.loop();
  // // client.publish("esp32/humidity", "asdf"); 发布主题
  // delay(3000);
  boolean pyroelectric_val = getPyroelectricValue();
  Serial.println(pyroelectric_val);
  if (pyroelectric_val == 1)
  {
    lcdOn();
  } else {
    lcdOff();
  }

}


