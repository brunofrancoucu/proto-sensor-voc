#ifndef ACTUATORS_H
#define ACTUATORS_H

struct ActuatorPins
{
    uint8_t REL;
    uint8_t BTN;
};

void setupActuators(ActuatorPins pins);
void runActuators();

#endif
