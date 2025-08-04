#include "ui/display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
// Internal
#include "ui/components.h"
#include "state.h"

static Adafruit_SSD1306 oled(128, 64, &Wire, -1);

namespace {
    void initSetup(DisplayPins pins)
    {
        Wire.begin(pins.SDA, pins.SCL);
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        welcome::paint(oled);
        oled.display();
    }
    
    void cycle()
    {
        std::vector<std::string> labels = {"Sensores", "Medir", "Ajustes", "Conectar", "Volumen"};
        int &act = state.display.activeOpt;
        int &foc = state.display.focusedOpt;

        oled.clearDisplay();
        oled.setCursor(0, 0);
    
        navbar::paint(oled, {
            .clock = "12:34",
            .alertIcon = false,
            .wifiIcon = true
        });

        switch (state.display.mode) 
        {
        case UIMode::Navigation:

            btmbar::paint(oled, {
                .txtL = labels[(foc + labels.size() - 1) % (labels.size() - 1)],
                .txtR = labels[(foc + labels.size() + 1) % (labels.size() - 1)]
            });
            
            menu::paint(oled, {
                // icons = [bitmaps]
                .labels = labels,
                .focused = foc,
            });

            break;
        case UIMode::Adjustment:

            btmbar::paint(oled, {
                .txtL = "SUBIR",
                .txtR = "BAJAR"
            });

            switch (state.display.activeOpt) {
                case 0: // Sensors
                    sensors::paint(oled, {
                    .temp = static_cast<int>(state.air.temp),
                    .hum = static_cast<int>(state.air.hum)
                });
                break;
            }

            break;
        }
        oled.display();
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);