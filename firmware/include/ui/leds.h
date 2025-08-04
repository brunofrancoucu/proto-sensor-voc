#ifndef LEDS_H
#define LEDS_H

#include <cstdint>
#include "cycle.h"

struct LedPins
{
    uint8_t GRN;
    uint8_t brightness;
};

extern CycleComp<LedPins> leds;

#endif
