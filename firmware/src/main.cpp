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

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0)); // seed 0 entropy
  delay(1500);

  // Initialize components
  setupDisplay({.SDA = 33, .SCL = 32});
  setupSensors({.MQ = 35, .DHT = 25});
  setupActuators({.REL = 26, .BTN = 21});
  setupSpot({
      .SSID = "E5-VOC-" + String(random(1000, 9999)),
      .PWD = String(random(10004321, 99994321)),
  });
  setupBuzzer({.BZR = 27, .VOL = 4});
  setupRFID({.SDA = 4, .SCK = 18, .MOSI = 23, .MISO = 19, .RST = 21});
}

void loop()
{
  delay(1000);

  // Loop components
  runDisplay();
  runSensors();
  runActuators();
  runSpot();
  runBuzzer();
  runRFID();
}