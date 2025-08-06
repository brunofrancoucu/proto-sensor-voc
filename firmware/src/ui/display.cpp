#include "ui/display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
// Internal
#include "ui/components.h"
#include "ui/screens.h"
#include "state.h"
#include "helpers/format.h"

static Adafruit_SSD1306 oled(128, 64, &Wire, -1);

namespace {
    void initSetup(DisplayPins pins)
    {
        Wire.begin(pins.SDA, pins.SCL);
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        welcome::paint(oled);
        oled.display();

        // Initialize variables & mem
    }
    
    void cycle()
    {
        oled.clearDisplay();
        oled.setCursor(0, 0);

        // Reference aliases 
        int &act = state.display.activeOpt;
        int &foc = state.display.focusedOpt;
        UIMode& mode = state.display.mode;
    
        navbar::paint(oled, {
            .clock = std::string(msToClock(millis()).c_str()),
            .alert = {.blink = true},
            .ap = {.blink = true},
            .wifi = {.blink = false},
            .bt = {.blink = false}
        });

        (mode == UIMode::Navigation) && ([&](){ menu::paint(oled); }, 0);
        (mode == UIMode::Dashboard) && ([&](){ dashboard::paint(oled); }, 0);
        (mode == UIMode::Notification) && Serial.println("Mode: Notification");

        btmbar::paint(oled, {
            .txtL = state.display.content.btmbarTxtL,
            .txtR = state.display.content.btmbarTxtR
        });
        
        oled.display();         
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);