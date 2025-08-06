#include "hmi/buttons.h"
#include "helpers/input.h"
#include "core/state.h"

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
        UIState& display = state.display;

        /**
         * Workflow: pressed event within module / comp (gamified)
        */
        updateButton(pins.LFT, state.input.LFT, [](){ display.nav(Nav::PREV); });
        updateButton(pins.MID, state.input.MID, [](){ display.select(); });
        updateButton(pins.RGT, state.input.RGT, [](){ display.nav(Nav::NEXT); });
    }
}


decltype(buttons) buttons = makeCycleComp(initSetup, cycle);