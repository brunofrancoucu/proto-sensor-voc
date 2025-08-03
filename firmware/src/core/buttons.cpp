#include "core/buttons.h"
#include "helpers/input.h"
#include "state.h"

namespace {
    ButtonPins pins;

    void initSetup(ButtonPins rPins)
    {
        pins = std::move(rPins);
        /*
         * Enable internal pull-up resistor:
         * This keeps the input HIGH when not pressed
         * Button should connect pin to GND when pressed (reads LOW).
        */
        pinMode(pins.LFT, INPUT_PULLUP);
        pinMode(pins.MID, INPUT_PULLUP);
        pinMode(pins.RGT, INPUT_PULLUP);
    }

    void cycle()
    {
        /**
         * Workflow: pressed event within module / comp (gamified)
        */
        updateButton(pins.LFT, state.input.LFT);
        updateButton(pins.MID, state.input.MID);
        updateButton(pins.RGT, state.input.RGT);
    }
}


decltype(buttons) buttons = makeCycleComp(initSetup, cycle);