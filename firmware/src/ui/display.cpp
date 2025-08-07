#include "ui/display.h"
#include <Wire.h>
// Internal
#include "ui/components.h"
#include "ui/views.h"
#include "core/state.h"
#include "helpers/format.h"

static auto& oled = state.display.oled;

namespace {
    void initSetup(DisplayPins pins)
    {
        Wire.begin(pins.SDA, pins.SCL);
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        welcomeView.paint();
        oled.display();
        // Initialize variables & mem
        state.display.activeView = &menuView;
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
            .bat = {.blink = state.system.battery < 20}
        });

        // Render View Page
        state.display.activeView->paint();

        btmbar::paint({
            .txtL = state.display.content.btmbarTxtL,
            .txtR = state.display.content.btmbarTxtR
        });
        
        oled.display();         
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);