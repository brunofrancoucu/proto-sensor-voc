#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include "cycle.h"

struct DisplayPins
{
    uint8_t SDA;
    uint8_t SCL;
};

extern CycleComp<DisplayPins> display;

#endif
