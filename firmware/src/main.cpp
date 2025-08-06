// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "core/state.h"
// Input (sensors, actuators, rfid)
#include "ap/spot.h"
#include "hmi/actuators.h"
#include "hmi/sensors.h"
#include "hmi/rfid.h"
#include "hmi/buttons.h"
// Output (user control)
#include "ui/display.h"
#include "ui/buzzer.h"
#include "ui/leds.h"

AppState state;

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0)); // use entropy
  delay(200);

  spot.setup({
    .SSID = "E5-VOC-" + String(random(1000, 9999)),
    .PWD = String(random(10004321, 99994321))
  });
  sensors.setup({.MQ = 35, .DHT = 25});
  actuators.setup({.REL = 26, .BTN = 21});
  rfid.setup({.SDA = 5, .SCK = 18, .MOSI = 23, .MISO = 19, .RST = 21});
  // Core (Inputs)
  buttons.setup({.LFT = 17, .MID = 16, .RGT = 4});
  // Interface
  display.setup({.SDA = 33, .SCL = 32});
  buzzer.setup({.BZR = 22, .VOL = 128});
  leds.setup({.GRN = 2});
}

void loop()
{
  spot.run();
  sensors.run(2000); // 250ms DHT (false on UI)
  actuators.run();
  rfid.run();
  // Core (inputs)
  buttons.run(50);
  // Interface
  display.run(33.33); // 30 FPS
  buzzer.run();
  leds.run();
}