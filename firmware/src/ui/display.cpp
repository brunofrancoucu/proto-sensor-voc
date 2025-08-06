#include "ui/display.h"
#include <Wire.h>
// Internal
#include "ui/components.h"
#include "ui/screens.h"
#include "core/state.h"
#include "helpers/format.h"

// Reference aliases
static auto& oled = state.display.oled;
static const int &act = state.display.activeOpt;
static const int &foc = state.display.focusedOpt;
static const UIMode& mode = state.display.mode;

namespace {
    void initSetup(DisplayPins pins)
    {
        Wire.begin(pins.SDA, pins.SCL);
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        welcome::paint();
        oled.display();
        // Initialize variables & mem
    }
    
    void cycle()
    {
        oled.clearDisplay();
        oled.setCursor(0, 0);

        navbar::paint({
            .clock = String(msToClock(millis())),
            .alert = {.blink = true},
            .ap = {.blink = true},
            .wifi = {.blink = false},
            .bt = {.blink = false}
        });

        mode == UIMode::Navigation ? menu::paint() : void();
        mode == UIMode::Dashboard ? dashboard::paint() : void();
        (mode == UIMode::Notification) && Serial.println("Mode: Notification"); // TODO: independent of UIMode

        btmbar::paint({
            .txtL = state.display.content.btmbarTxtL,
            .txtR = state.display.content.btmbarTxtR
        });
        
        oled.display();         
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);