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
                auto nots = state.display.notifications.lock();
                if (nots && !nots->empty()) {
                    // Override view input
                    (*nots)[0]->onInput(button);
                } else {
                    state.display.activeView->onInput(button);
                }
            });
        }
    }
}

decltype(buttons) buttons = makeCycleComp(initSetup, cycle);