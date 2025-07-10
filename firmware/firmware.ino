// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "data/state.h"
#include "ui/display.h"
#include "hmi/actuators.h"
#include "hmi/sensors.h"
#include "hmi/spot.h"
// TODO: use PlatformIO auto-compile cpp in subfolders
#include "data/state.cpp"
#include "ui/display.cpp"
#include "hmi/actuators.cpp"
#include "hmi/sensors.cpp"
#include "hmi/spot.cpp"

void setup()
{
  Serial.begin(115200);

  // Initialize components
  setupDisplay(33, 32);
  setupSensors(35, 25);
  setupActuators(26, 21);
  setupSpot();

  delay(1500);
}

void loop()
{
  // Loop components
  runDisplay();
  static unsigned long last = 0;
  if (millis() - last >= 2000)
  {                  // if 2s have passed
    last = millis(); // update the timer
  }
  runSensors();
  runActuators();
  runSpot();

  delay(1000);
}