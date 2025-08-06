#ifndef BUTTONS_H
#define BUTTONS_H

#include "core/cycle.h"

struct ButtonPins {
    uint8_t LFT;
    uint8_t MID;
    uint8_t RGT;
};

extern CycleComp<ButtonPins> buttons;

#endif // BUTTONS_H