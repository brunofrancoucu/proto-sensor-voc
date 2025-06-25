// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "State.h"
#include "Vent.h"
#include "Display.h"
#include "Sensors.h"
#include "Spot.h"

void setup()
{
  Serial.begin(115200);

  // Initialize components
  setupDisplay(33, 32);
  setupSensors(35, 25);
  setupVent(26, 21);
  setupSpot();

  delay(1500);
}

void loop()
{
  // Loop components
  runDisplay();
  runSensors();
  runVent();
  runSpot();

  // display.display();

  delay(2000);
}