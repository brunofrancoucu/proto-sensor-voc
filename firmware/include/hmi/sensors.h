#ifndef SENSORS_H
#define SENSORS_H

#include "core/cycle.h"

struct SensorsPins
{
    uint8_t MQ;
    uint8_t DHT;
};

// Export
extern CycleComp<SensorsPins> sensors;

#endif