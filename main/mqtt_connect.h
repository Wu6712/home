#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "led.h"
#include "tem_hum.h"
#include "water_drop.h"
#include "gas.h"

const char* mqtt_server = "test.mosquitto.org";
WiFiClient espClient;
PubSubClient client(espClient);
char* topicsArray[] = {"温湿度传感器", "水滴传感器", "pin", "气体传感器"};
int arrayLength = sizeof(topicsArray) / sizeof(topicsArray[0]);

// mqtt回调
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  // 解析JSON字符串
  StaticJsonDocument<200> doc;
  deserializeJson(doc, message, length);

  // 获取json属性值
  const char* msg = doc["msg"];
  const char* temperature = doc["temperature"];
  const char* water_drop = doc["water_drop"];
  const char* gas = doc["gas"];

  Serial.println("temperature...");
  Serial.println(temperature);

  Serial.println("msg...");
  Serial.println(msg);

  Serial.println("water_drop...");
  Serial.println(water_drop);

  Serial.println("gas...");
  Serial.println(gas);

  // 对元件进行简单操作
  if (String(topic) == "pin") {                        // 灯泡
    Serial.print("Changing output to ");
    if(strcmp(msg, "on") == 0) {
      Serial.println("on");
      ledOn();
    }
    else if(strcmp(msg, "off") == 0) {
      Serial.println("off");
      ledOff();
    }else if (strcmp(msg, "getState") == 0) {
      // client.publsh("pin", );
      String sendMsg = "{\"msg\":\"" + readLedState() + "\"}";
      client.publish("resPin", sendMsg.c_str());
    }
  } else if (String(topic) == "温湿度传感器") {        // 温湿度操作
    Serial.println("返回温湿度数据");
    String sendMsg =  "{\"temperature\":\"" + readTem() + "\",\"humidity\":\"" + readHum() + "\"}";
    client.publish("resTemAndHum", sendMsg.c_str());
  } else if (String(topic) == "水滴传感器") {           // 水滴传感器
    if (strcmp(water_drop, "getState") == 0) {
      String sendMsg = "{\"msg\":\"" + readWaterDropState() + "\"}";
      client.publish("resWaterDrop", sendMsg.c_str());
    }
  } else if (String(topic) == "气体传感器") {
      if (strcmp(gas, "getState") == 0) {
      String sendMsg = "{\"msg\":\"" + getGasValue() + "\"}";
      client.publish("resGas", sendMsg.c_str());
    }
  }

  

}

// 订阅主题方法
void subscribeTopic(char** topicsArray, int arrayLength) {
  for (int i = 0; i < arrayLength; i++) {
    Serial.println(topicsArray[i]);
    client.subscribe(topicsArray[i]);
  }
  
}

// 重连,订阅
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("nba")) { // 连接
      Serial.println("connected");
      subscribeTopic(topicsArray, arrayLength); // 订阅
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


#endif

