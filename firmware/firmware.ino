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
  delay(1500);

  // Initialize components
  setupDisplay({.SDA = 33, .SCL = 32});
  setupSensors({.MQ = 35, .DHT = 25});
  setupActuators({.REL = 26, .BTN = 21});
  setupSpot();
}

void loop()
{
  delay(1000);

  // Loop components
  runDisplay();
  runSensors();
  runActuators();
  runSpot();
}