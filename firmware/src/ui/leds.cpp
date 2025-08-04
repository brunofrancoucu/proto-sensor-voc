#include "ui/leds.h"

namespace {
    LedPins pins;
    static unsigned long lastBlink = 0;
    static bool state = false;
    static uint8_t brightness;

    void initSetup(LedPins confPins = {2, 128})
    {
        pins = confPins;
        pins.brightness = confPins.brightness ? confPins.brightness : 128;

        pinMode(pins.GRN, OUTPUT);
        analogWrite(pins.GRN, 0);
    }

    void cycle()
    {
        // Example: Blink GREEN LED every second
        if (millis() - lastBlink >= 1000) {
            lastBlink = millis();
            analogWrite(pins.GRN, pins.brightness);
        } else {
            analogWrite(pins.GRN, 0);
        }
    }
}

decltype(leds) leds = makeCycleComp(initSetup, cycle);