// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "State.h"
// #include "Vent.h"
#include "Display.h"
#include "Sensors.h"
#include "Spot.h"

void setup()
{
  Serial.begin(115200);

  // Initialize components
  setupDisplay(33, 32);
  setupSensors(35, 25);
  // setupVent(26, 21);
  setupSpot();

  delay(1500);
}

void loop()
{
  // Loop components
  runDisplay();
  // This wastes CPU, stresses your ESP32, crashes slower sensors like DHT11, and can trigger watchdog resets.
  static unsigned long last = 0;
  if (millis() - last >= 2000)
  {                  // if 2s have passed
    last = millis(); // update the timer
    runSensors();    // read sensors only now
  }
  // runVent();
  runSpot();

  // display.display();

  delay(1000);
}