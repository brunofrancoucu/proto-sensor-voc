#include "ui/instances.h"
#include "core/state.h"
#include "ui/atomic.h"

#include <vector>
#include <memory>

static auto& oled = state.display.oled;

void SpotInfoNotf::paint() {
    paintNotfBox("Como Usar?", "WiFi => " + state.hotspot.SSID);
    btnLabels[0] = "Volver";
    paintNotfBtns(btnLabels, focusedBtn);
}

void SpotInfoNotf::onInput(Button& button) {
    if (button.pin == state.input.pins.MID && focusedBtn == 0) state.display.notifications.remove(this);
    if (button.pin == state.input.pins.LFT) moveCursor(-1);
    if (button.pin == state.input.pins.RGT) moveCursor(1);
}