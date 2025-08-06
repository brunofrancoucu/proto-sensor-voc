#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "core/cycle.h"

struct ActuatorPins
{
    uint8_t REL;
    uint8_t BTN;
};

extern CycleComp<ActuatorPins> actuators;

#endif
