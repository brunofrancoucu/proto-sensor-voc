#include "ui/instances.h"
#include "core/state.h"

#include <vector>
#include <memory>

RFIDScannedNot rfidScannedNot({ "RFID Scanned"});

auto& oled = state.display.oled;

void RFIDScannedNot::paint() {
    // Paint the notification content on the display
    oled.setCursor(0, 0);
    oled.print(content.msg);
}

void RFIDScannedNot::onInput(Button& button) {
    // Handle button input for the notification
    if (button.pin == state.input.pins.MID) {
        // Remove the notification on MID button press
        selfRemove();
    } else if (button.pin == state.input.pins.LFT || button.pin == state.input.pins.RGT) {
        // Optionally handle LFT or RGT button presses
        // For example, you could log or display a message
    }
}