#include <Wire.h>
#include "wifi_connect.h"
#include "mqtt_connect.h"
#include "led.h"
#include "water_drop.h"
#include "gas.h"

long lastMsg = 0;
char msg[50];

int value = 0;

void setup() {
  Serial.begin(115200); // 串口
  setup_wifi(); // 连接WiFi
  // mqtt
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // 灯泡
  ledInit();
  // 水滴传感器
  initWaterDrop();
  // 气体传感器
  gasInit();


}


void loop() {
  // 检查mqtt连接情况
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}


