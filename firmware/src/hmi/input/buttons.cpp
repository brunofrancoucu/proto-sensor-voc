#include "hmi/buttons.h"
#include "core/state.h"

namespace {
    void initSetup(ButtonPins rPins)
    {
        // Init Button instance for each btn pin
        state.input.pins = rPins;
        state.input.buttons = {
            Button(rPins.LFT),
            Button(rPins.MID),
            Button(rPins.RGT)
        };
    }

    void cycle()
    {
        // Handle button presses for each Button
        for (Button& button : state.input.buttons) {
            button.onPress([&]() {
                if (state.display.notifications.size() > 0) {
                    // Override view input
                    state.display.notifications.onInput(button);
                } else {
                    state.display.activeView->onInput(button);
                }
            });
        }
    }
}

decltype(buttons) buttons = makeCycleComp(initSetup, cycle);