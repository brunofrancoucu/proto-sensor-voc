#ifndef LEDS_H
#define LEDS_H

#include <cstdint>
#include "core/cycle.h"

struct LedPins
{
    uint8_t GRN;
    // Default brightness
    uint8_t brightness;
};

extern CycleComp<LedPins> leds;

#endif
