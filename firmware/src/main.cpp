// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "state.h"
#include "display.h"
#include "actuators.h"
#include "sensors.h"
#include "spot.h"
#include "buzzer.h"
#include "rfid.h"
#include "cycle.h"

auto sensors = makeCycleComp(setupSensors, runSensors);
auto display = makeCycleComp(setupDisplay, runDisplay);
auto actuators = makeCycleComp(setupActuators, runActuators);
auto spot = makeCycleComp(setupSpot, runSpot);
auto buzzer = makeCycleComp(setupBuzzer, runBuzzer);
auto rfid = makeCycleComp(setupRFID, runRFID);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  randomSeed(analogRead(0)); // seed 0 entropy
  delay(1500);

  // Initialize components
  actuators.setup({.REL = 26, .BTN = 21});
  sensors.setup({.MQ = 35, .DHT = 25});
  display.setup({.SDA = 33, .SCL = 32});
  buzzer.setup({.BZR = 27, .VOL = 128});
  rfid.setup({.SDA = 5, .SCK = 18, .MOSI = 23, .MISO = 19, .RST = 21});
  spot.setup({
    .SSID = "E5-VOC-" + String(random(1000, 9999)),
    .PWD = String(random(10004321, 99994321))
  });
}

void loop()
{
  // Loop components
  sensors.run(2000);
  display.run();
  actuators.run();
  spot.run();
  buzzer.run();
  rfid.run();
}