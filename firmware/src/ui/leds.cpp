#include "ui/leds.h"

namespace {
    LedPins pins;
    static unsigned long lastBlink = 0;

    void initSetup(LedPins confPins)
    {
        pins = confPins;
        pinMode(pins.GRN, OUTPUT);
        digitalWrite(pins.GRN, LOW);
    }

    void cycle()
    {
        // Example: Blink GREEN LED every second
        if (millis() - lastBlink >= 1000) {
            lastBlink = millis();
            digitalWrite(pins.GRN, !digitalRead(pins.GRN));
        }
    }
}

decltype(leds) leds = makeCycleComp(initSetup, cycle);