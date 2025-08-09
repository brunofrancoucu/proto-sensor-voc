#include "ui/instances.h"
#include "core/state.h"
#include "ui/atomic.h"
#include "helpers/blink.h"

static const unsigned char PROGMEM image_weather_windsock_bits[] = {0x00,0x00,0x80,0x00,0xcf,0x00,0xb6,0xf0,0xab,0x68,0xab,0x68,0x97,0xf0,0x9c,0x00,0xa0,0x00,0xc0,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00};
static const unsigned char PROGMEM image_weather_wind_bits[] = {0x00,0x00,0x00,0x00,0x00,0x30,0x03,0x88,0x04,0x44,0x04,0x44,0x00,0x44,0x00,0x88,0xff,0x32,0x00,0x00,0xad,0x82,0x00,0x60,0x00,0x10,0x00,0x10,0x01,0x20,0x00,0xc0};
ScanView scanView("Medir", image_weather_windsock_bits);

static auto& oled = state.display.oled;

void ScanView::paint() {
    // none
    blinkIf(true, [&](){paintStatBox(image_weather_wind_bits, "--- -s", 8, 16);}, -100);
    blinkIf(false, [&](){paintStatBox(image_weather_windsock_bits, "--- -s", 8, 16 + 14 + 4);}, -100);

    // Graph
    oled.drawLine(78, 16, 78, 48, 1);
    oled.drawLine(122, 46, 76, 46, 1);
}

void ScanView::onInput(Button& button) {
    if (button.pin == state.input.pins.RGT) {
        // RGT();
        state.display.notifications.add(new RFIDScannedNotf({"Iniciar medicion?"}, {"Si", "No"}));
    } else {
        // No action for LFT/MID
        state.display.navTo(&menuView);
    }
}

void ScanView::enter() {
    btmbar.content.txtL = "Volver";
    btmbar.content.txtR = "Iniciar";
}