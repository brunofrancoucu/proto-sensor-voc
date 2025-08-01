#ifndef RFID_H
#define RFID_H

#include "cycle.h"

struct RfidPins
{
    uint8_t SDA;
    uint8_t SCK;
    uint8_t MOSI;
    uint8_t MISO;
    uint8_t RST;
};

// Export
extern CycleComp<RfidPins> rfid;

#endif