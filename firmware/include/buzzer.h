#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

struct BuzzerPins
{
  uint8_t BZR;
  uint8_t VOL;
};

void playTone(int freq, int duration);
void setupBuzzer(BuzzerPins pins);
void runBuzzer();

#endif