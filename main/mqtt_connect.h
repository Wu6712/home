#ifndef MQTT_CONNECT_H
#define MQTT_CONNECT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "lcd.h"

const char* mqtt_server = "test.mosquitto.org";
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "lcd") { // 这里测试，只测试一个灯泡
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      lcdOn();
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      lcdOff();
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("nba")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("pin");  // 订阅主题
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