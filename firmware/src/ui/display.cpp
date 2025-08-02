#include "drivers/display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
// Internal
#include "state.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

namespace {
    void initSetup(DisplayPins pins)
    {
        Wire.begin(pins.SDA, pins.SCL);
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);
        oled.setCursor(0, 0);
        oled.println("Bienvenido");
        oled.display();
    }
    
    void cycle()
    {
        oled.clearDisplay();
        oled.setCursor(0, 0);

        if (!isnan(state.air.temp) && !isnan(state.air.hum))
        {
            oled.print("Temp: ");
            oled.print(state.air.temp, 1);
            oled.println(" C");
            oled.print("Humedad: ");
            oled.print(state.air.hum, 0);
            oled.println(" %");
        }
        else
        {
            oled.println("Error DHT11");
        }
    
        oled.print("Aire: ");
        oled.println(state.air.status);
        oled.display();
    }
}

decltype(display) display = makeCycleComp(initSetup, cycle);