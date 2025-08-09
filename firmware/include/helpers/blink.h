#ifndef BLINLK_H
#define BLINLK_H

#include <Arduino.h>

struct Blink {
    unsigned long last_ms = 0;
};

void blinkIf(bool condition, std::function<void()> drawCb, unsigned long offset = 0);

#endif // BLINK_H