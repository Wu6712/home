#include <Wire.h>
#include "wifi_connect.h"
#include "mqtt_connect.h"
#include "pinMode.h"

#define led_y 12

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  pinInit();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // client.publish("esp32/humidity", "asdf"); 发布主题
  delay(3000);
}