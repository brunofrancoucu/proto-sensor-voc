#include "ui/leds.h"
#include "core/state.h"

namespace {
    LedPins pins;
    static unsigned long lastBlink = 0;
    static uint8_t brightness;

    void initSetup(LedPins confPins = {2, 128})
    {
        pins = confPins;

        pinMode(pins.GRN, OUTPUT);
        analogWrite(pins.GRN, 0);
    }

    void cycle()
    {
        // Example: Blink GREEN LED every second
        if (millis() - lastBlink >= 1000) {
            lastBlink = millis();
            analogWrite(pins.GRN, state.system.brightness);
        } else {
            analogWrite(pins.GRN, 0);
        }
    }
}

decltype(leds) leds = makeCycleComp(initSetup, cycle);