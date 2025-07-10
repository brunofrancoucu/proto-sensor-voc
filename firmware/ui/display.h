#include <cstdint>

#ifndef DISPLAY_H
#define DISPLAY_H

struct DisplayPins
{
    uint8_t SDA;
    uint8_t SCL;
};

void setupDisplay(DisplayPins pins);
void runDisplay();

#endif
