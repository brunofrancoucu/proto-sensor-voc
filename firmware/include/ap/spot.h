#ifndef SPOT_H
#define SPOT_H

#include "core/cycle.h"

struct SpotConfig
{
    String SSID;
    String PWD;
};

extern CycleComp<SpotConfig> spot;

#endif
