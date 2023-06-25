#ifndef __MQTT_CONNECT_H__
#define __MQTT_CONNECT_H__

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "led.h"
#include "tem_hum.h"
#include "water_drop.h"
#include "gas.h"
#include "servos.h"
#include "rfid.h"
#include "fan.h"
#include "pyroelectric.h"

const char* mqtt_server = "test.mosquitto.org";
WiFiClient espClient;
PubSubClient client(espClient);
char* topicsArray[] = {"温湿度传感器", "水滴传感器", "灯", "气体传感器", "风扇", "门", "窗户", "红外"};
int arrayLength = sizeof(topicsArray) / sizeof(topicsArray[0]);

void ledMqtt(const char* msg)
{
  Serial.println("ledMethod...");
  if(strcmp(msg, "on") == 0) {
    Serial.println("on");
    ledOn();
  } else if(strcmp(msg, "off") == 0) {
    Serial.println("off");
    ledOff();
  } else if(strcmp(msg, "getState") == 0) {
    StaticJsonDocument<200> ledDoc;
    ledDoc["ledState"] = readLedState();
    String ledMsg;
    serializeJsonPretty(ledDoc, ledMsg);
    client.publish("resLed", ledMsg.c_str());
  }
}


void temHumMqtt()
{
  StaticJsonDocument<200> temHumDoc;
  temHumDoc["temperature"] = readTem();
  temHumDoc["humidity"] = readHum();
  String temHumMsg;
  serializeJsonPretty(temHumDoc, temHumMsg);
  client.publish("resTemAndHum", temHumMsg.c_str());
}


void waterDropMqtt()
{
  StaticJsonDocument<200> waterDropDoc;
  waterDropDoc["waterDropValue"] = readWaterDropState();
  String waterDropMsg;
  serializeJsonPretty(waterDropDoc, waterDropMsg);
  client.publish("resWaterDrop", waterDropMsg.c_str());
}


void gasMqtt()
{
  StaticJsonDocument<200> gasDoc;
  gasDoc["gasValue"] = getGasValue();
  String gasMsg;
  serializeJsonPretty(gasDoc, gasMsg);
  client.publish("resGas", gasMsg.c_str());
}

void doorMqtt(const char* msg)
{
  if(strcmp(msg, "on") == 0) {
    Serial.println("on");
    openTheDoor();
  } else if(strcmp(msg, "off") == 0) {
    Serial.println("off");
    closeTheDoor();
  } else if(strcmp(msg, "getState") == 0) {
    StaticJsonDocument<200> doorDoc;
    doorDoc["doorState"] = readDoorState();
    String doorMsg;
    serializeJsonPretty(doorDoc, doorMsg);
    client.publish("resDoor", doorMsg.c_str());
  }
}


void windowMqtt(const char* msg)
{
  if(strcmp(msg, "on") == 0) {
    Serial.println("on");
    openTheWindow();
  } else if(strcmp(msg, "off") == 0) {
    Serial.println("off");
    closeTheWindow();
  } else if(strcmp(msg, "getState") == 0) {
    StaticJsonDocument<200> windowDoc;
    windowDoc["windowState"] = readWindowState();
    String windowMsg;
    serializeJsonPretty(windowDoc, windowMsg);
    client.publish("resWindow", windowMsg.c_str());
  }
}


void fanMqtt(const char* msg)
{
  if(strcmp(msg, "0") == 0) {
    changeFanGear(0);
  } else if(strcmp(msg, "1") == 0) {
    changeFanGear(1);
  } else if(strcmp(msg, "2") == 0) {
    changeFanGear(2);
  } else if(strcmp(msg, "3") == 0) {
    changeFanGear(3);
  } else if(strcmp(msg, "getState") == 0) {
    StaticJsonDocument<200> fanDoc;
    fanDoc["fanState"] = readFanGear();
    String fanMsg;
    serializeJsonPretty(fanDoc, fanMsg);
    client.publish("resFan", fanMsg.c_str());
  }
}


void pyroelectricMqtt()
{
  StaticJsonDocument<200> pyroelectricDoc;
  pyroelectricDoc["pyroelectricState"] = getPyroelectricValue();
  String pyroelectricMsg;
  serializeJsonPretty(pyroelectricDoc, pyroelectricMsg);
  client.publish("resPyroelectric", pyroelectricMsg.c_str());
}

void getAllState()
{

  // 创建一个JSON对象
  StaticJsonDocument<200> allDoc;
  // 灯
  String ledState = readLedState();
  allDoc["ledState"] = ledState;
  // 温度
  String temState = readTem();
  allDoc["temState"] = temState;
  // 湿度
  String hemState = readHum();
   allDoc["hemState"] = hemState;
  // 气体
  String gasState = getGasValue();
  allDoc["gasState"] = gasState;
  // 水滴
  String waterDropState = readWindowState();
  allDoc["waterDropState"] = waterDropState;
  // 风扇
  String fanState = readFanGear();
  allDoc["fanState"] = fanState;
  // 门
  String doorState = readDoorState();
  allDoc["doorState"] = doorState;
  // 窗户
  String windowState = readWindowState();
  allDoc["windowState"] = windowState;
  // 红外
  String pyroelectricState = getPyroelectricValue();
  allDoc["pyroelectricState"] = pyroelectricState;

  String sendMsg;
  serializeJsonPretty(allDoc, sendMsg);

  client.publish("allState", sendMsg.c_str());
}

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

  Serial.println("msg...");
  Serial.println(msg);

  // 对单个元件进行简单操作
  if (String(topic) == "灯") {                      // 灯
    ledMqtt(msg);
  } else if (String(topic) == "温湿度传感器") {        // 温湿度操作
    temHumMqtt();
  } else if (String(topic) == "水滴传感器") {          // 水滴传感器
    waterDropMqtt();
  } else if (String(topic) == "气体传感器") {          // 气体
      gasMqtt();
  } else if (String(topic) == "门") {                 // 门
      doorMqtt(msg);
  } else if (String(topic) == "窗户") {                // 窗户
    windowMqtt(msg);
  } else if (String(topic) == "风扇") {                // 风扇
    fanMqtt(msg);
  } else if (String(topic) == "红外") {                 // 红外
    pyroelectricMqtt();
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

