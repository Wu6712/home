#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <ESP32Tone.h>
#include <musicESP32_home.h>
music Music(25);
#define buzzer_pin 25

void buzzerInit()
{
  pinMode(buzzer_pin, OUTPUT);
}

void alarm()
{
  digitalWrite(buzzer_pin,HIGH);
}

void cancelAlarm()
{
  digitalWrite(buzzer_pin,LOW);
}

void playMusic()
{
  Music.Ode_to_Joy();
}

#endif