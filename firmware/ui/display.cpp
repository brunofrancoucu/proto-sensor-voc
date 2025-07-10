#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
// Internal
#include "display.h"
#include "data/state.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupDisplay(DisplayPins pins)
{
    Wire.begin(pins.SDA, pins.SCL);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bienvenido");
    display.display();
}

void runDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);

    if (!isnan(state.temperature) && !isnan(state.humidity))
    {
        display.print("Temp: ");
        display.print(state.temperature, 1);
        display.println(" C");
        display.print("Humedad: ");
        display.print(state.humidity, 0);
        display.println(" %");
    }
    else
    {
        display.println("Error DHT11");
    }

    display.print("Aire: ");
    display.println(state.air);
    display.display();
}