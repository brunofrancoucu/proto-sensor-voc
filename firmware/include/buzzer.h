#ifndef BUZZER_H
#define BUZZER_H

#include "cycle.h"

struct BuzzerPins
{
  uint8_t BZR;
  uint8_t VOL;
};

void playTone(int freq, int duration);

extern CycleComp<BuzzerPins> buzzer;

#endif