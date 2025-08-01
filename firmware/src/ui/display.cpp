#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
// Internal
#include "display.h"
#include "state.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 disp(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupDisplay(DisplayPins pins)
{
    Wire.begin(pins.SDA, pins.SCL);
    disp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    disp.clearDisplay();
    disp.setTextSize(1);
    disp.setTextColor(SSD1306_WHITE);
    disp.setCursor(0, 0);
    disp.println("Bienvenido");
    disp.display();
}

void runDisplay()
{
    disp.clearDisplay();
    disp.setCursor(0, 0);

    if (!isnan(state.temperature) && !isnan(state.humidity))
    {
        disp.print("Temp: ");
        disp.print(state.temperature, 1);
        disp.println(" C");
        disp.print("Humedad: ");
        disp.print(state.humidity, 0);
        disp.println(" %");
    }
    else
    {
        disp.println("Error DHT11");
    }

    disp.print("Aire: ");
    disp.println(state.air);
    disp.display();
}