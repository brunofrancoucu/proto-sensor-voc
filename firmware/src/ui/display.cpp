#include "ui/display.h"
#include <Wire.h>
// Internal
#include "ui/interfaces.h"
#include "ui/instances.h"
#include "core/state.h"

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
        state.display.activeView->enter();
    }
    
    void cycle()
    {
        oled.clearDisplay();
        oled.setCursor(0, 0);

        state.display.activeView->paint();
        navbar.paint();
        btmbar.paint();
        state.display.notifications.paint();
        
        oled.display();
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);