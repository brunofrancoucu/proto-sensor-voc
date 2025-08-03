#include "core/manager.h"
#include "state.h"

namespace
{
    void initSetup()
    {
        // Initialization logic for the manager can be added here
        Serial.println("Manager initialized.");
    }

    void cycle()
    {
        // Periodic tasks can be added here
        if (state.input.RGT.pressed)
        {
            if (state.display.mode == UIMode::Navigation && !state.input.RGT.usedOnce) {
                // Next View
                state.display.next();
                state.input.RGT.usedOnce = true;
            }
        }
        if (state.input.LFT.pressed)
        {
            if (state.display.mode == UIMode::Navigation && !state.input.LFT.usedOnce) {
                // Previous View
                state.display.prev();
                state.input.LFT.usedOnce = true;
            }
        }
        if (state.input.MID.pressed && !state.input.MID.usedOnce) 
        {
            if (state.display.mode == UIMode::Navigation) {
                // Adjustment Mode
                state.display.mode = UIMode::Adjustment;
                state.input.MID.usedOnce = true;
            } else if (state.display.mode == UIMode::Adjustment) {
                // Navigation Mode
                state.display.mode = UIMode::Navigation;
                state.input.MID.usedOnce = true;
            } else {
                // Handle notification
            }
        }
    }
}

decltype(manager) manager = makeCycleComp(initSetup, cycle);