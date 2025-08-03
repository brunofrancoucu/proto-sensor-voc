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
        if (state.input.RGT.pressed && !state.input.RGT.usedOnce)
        {
            state.display.next();
            state.input.RGT.usedOnce = true;
        }
    }
}

decltype(manager) manager = makeCycleComp(initSetup, cycle);