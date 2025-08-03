#include "core/manager.h"
#include "state.h"

namespace {
    void initSetup()
    {
        // Initialization logic for the manager can be added here
        Serial.println("Manager initialized.");
    }

    void cycle()
    {
        // C++17+ auto& [LFT, MID, RGT] = state.input;
        InputButton& LFT = state.input.LFT;
        InputButton& MID = state.input.MID;
        InputButton& RGT = state.input.RGT;
        DisplayState& display = state.display;

        // Periodic tasks can be added here TODO use switch
        switch (display.mode) {
            case UIMode::Navigation:
                // Next View
                if (RGT.pressed && !RGT.once) {
                    RGT.once = true;
                    display.next();
                }
                // Previous View
                if (LFT.pressed && !LFT.once) {
                    LFT.once = true;
                    display.prev();
                }
                // Selection
                if (MID.pressed && !MID.once) {
                    MID.once = true;
                    display.mode = UIMode::Adjustment;
                    display.select();
                }
                break;
            case UIMode::Adjustment:
                // Raise Selection
                if (RGT.pressed && !RGT.once) {
                    RGT.once = true;
                    display.next();
                }
                // Lower Selection
                if (LFT.pressed && !LFT.once) {
                    LFT.once = true;
                    display.prev();
                }
                // Selection
                if (MID.pressed && !MID.once) {
                    MID.once = true;
                    display.mode = UIMode::Navigation;
                    display.select();
                }
                // Handle adjustment mode tasks
                break;
            case UIMode::Notification:
                // Handle notification tasks
                break;
        };
        // if (MID.pressed && !MID.usedOnce) 
        // {
        //     if (state.display.mode == UIMode::Navigation) {
        //         // Adjustment Mode
        //         state.display.mode = UIMode::Adjustment;
        //         MID.usedOnce = true;
        //     } else if (state.display.mode == UIMode::Adjustment) {
        //         // Navigation Mode
        //         state.display.mode = UIMode::Navigation;
        //         MID.usedOnce = true;
        //     } else {
        //         // Handle notification
        //     }
        // }
    }
}

decltype(manager) manager = makeCycleComp(initSetup, cycle);