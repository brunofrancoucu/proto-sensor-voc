#include "ui/instances.h"
#include "core/state.h"

static const unsigned char PROGMEM image_weather_windsock_bits[] = {0x00,0x00,0x80,0x00,0xcf,0x00,0xb6,0xf0,0xab,0x68,0xab,0x68,0x97,0xf0,0x9c,0x00,0xa0,0x00,0xc0,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00};

ScanView scanView("Medir", image_weather_windsock_bits);

void ScanView::paint() {
    // none
}

void ScanView::onInput(Button& button) {
    if (button.pin == state.input.pins.RGT) {
        // RGT();
        // state.scan.isRunning = !state.scan.isRunning;
        // state.scan.motorSpeed = state.scan.isRunning ? 1 : 0; // on off, relay
        // btmbar.content.txtR = state.scan.isRunning ? "Detener" : "Iniciar";
        state.display.addNotification(std::make_shared<RFIDScannedNot>(rfidScannedNot));
    } else {
        // No action for LFT/MID
        state.display.navTo(&menuView);
    }
}

void ScanView::enter() {
    btmbar.content.txtL = "Volver";
    btmbar.content.txtR = "Iniciar";
}