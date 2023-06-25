#include <Wire.h>
#include "wifi_connect.h"
#include "mqtt_connect.h"
#include "led.h"
#include "water_drop.h"
#include "gas.h"
#include "btn1.h"
#include "btn2.h"
#include "rfid.h"
#include "servos.h"
#include "pyroelectric.h"
#include "fan.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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
  // 按钮1
  btn1Init();
  // 按钮2
  btn2Init();
  // 门禁
  rfidInit();
  // 门舵机
  doorServosInit();
  // 窗户舵机
  windowServosInit();
  // 红外感应
  pyroelectricInit();
  // 风扇
  fanInit();

  xTaskCreate(doorModuleTask, "doorModuleTask", 4096, NULL, 1, NULL);

}




void loop() {
  // 检查mqtt连接情况
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 5min上传一次数据
  if (millis() % (1000 * 60 * 5) == 0) {
    getAllState();
  }

}

void doorModuleTask(void *pvParameters) {
  while (1) {
    doorModule();
    vTaskDelay(100 / portTICK_RATE_MS); // 延时100ms
  }
}

