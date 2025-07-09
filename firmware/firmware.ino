// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "data/State.h"
#include "ui/Display.h"
#include "hmi/Actuators.h"
#include "hmi/Sensors.h"
#include "hmi/Spot.h"

// TODO: use PlatformIO auto-compile cpp in subfolders
#include "data/State.cpp"
#include "ui/Display.cpp"
#include "hmi/Actuators.cpp"
#include "hmi/Sensors.cpp"
#include "hmi/Spot.cpp"

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
    runSensors();    // read sensors only now
  }
  runActuators();
  runSpot();

  delay(1000);
}