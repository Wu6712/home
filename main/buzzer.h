#ifndef BUZZER_H
#define BUZZER_H

#include <ESP32Tone.h>
#include <musicESP32_home.h>
music Music(25);
#define buzzer_pin 25

void buzzerInit()
{
  pinMode(buzzer_pin, OUTPUT);
}

void playMusic()
{
  Music.Ode_to_Joy();
}

#endif