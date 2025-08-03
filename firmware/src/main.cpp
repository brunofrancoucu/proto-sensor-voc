// Dependencies
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// Internal
#include "state.h"
#include "drivers/display.h"
#include "drivers/actuators.h"
#include "drivers/sensors.h"
#include "drivers/spot.h"
#include "drivers/buzzer.h"
#include "drivers/rfid.h"
#include "drivers/buttons.h"

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0)); // use entropy
  delay(200);

  // Initialize components
  actuators.setup({.REL = 26, .BTN = 21});
  sensors.setup({.MQ = 35, .DHT = 25});
  display.setup({.SDA = 33, .SCL = 32});
  buttons.setup({.LFT = 34, .MID = 35, .RGT = 36});
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
  sensors.run(2000); // 250ms DHT (false on UI)
  actuators.run();
  spot.run();
  rfid.run();
  // Interface
  buttons.run();
  display.run(33.33); // 30 FPS
  buzzer.run();
}