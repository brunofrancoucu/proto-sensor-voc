#include "ui/components.h"
#include "core/state.h"
#include "helpers/blink.h"

static const unsigned char PROGMEM image_Alert_bits[] = {0x08,0x00,0x1c,0x00,0x14,0x00,0x36,0x00,0x36,0x00,0x7f,0x00,0x77,0x00,0xff,0x80};
static const unsigned char PROGMEM image_Battery_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xf0,0x10,0x08,0x32,0xa8,0x32,0xa8,0x10,0x08,0x0f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM image_BLE_beacon_bits[] = {0x44,0x92,0xaa,0x92,0x54,0x10,0x10,0x7c};
static const unsigned char PROGMEM image_Rpc_active_bits[] = {0xe0,0xac,0xe2,0x02,0x80,0x8e,0x6a,0x0e};

static auto& oled = state.display.oled;

// Icon blinks
static Blink alert;
static Blink ap;
static Blink wifi;
static Blink bat;


void navbar::paint(Config config) {
    // Layer 1
    oled.setCursor(50, 1);
    oled.print(config.clock.c_str());
    // Layer 2
    oled.drawLine(0, 9, 128, 9, 1);

    // Battery
    blinkIf(config.bat.blink, bat, [&](){ oled.drawBitmap(115, -4, image_Battery_bits, 16, 16, 1);}, 200);
    // Alert
    blinkIf(config.alert.blink, alert, [&](){ oled.drawBitmap(0, 0, image_Alert_bits, 9, 8, 1); }, 0);
    // BLE_beacon
    blinkIf(config.wifi.blink, wifi, [&](){ oled.drawBitmap(106, 0, image_BLE_beacon_bits, 7, 8, 1); }, 300);
    // Rpc_active
    blinkIf(config.ap.blink, ap, [&](){ oled.drawBitmap(94, 0, image_Rpc_active_bits, 7, 8, 1); }, 400);
}