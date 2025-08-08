#include "ui/instances.h"
#include "core/state.h"
#include "ui/atomic.h"
#include "helpers/oled.h"

#include <vector>
#include <memory>

auto& oled = state.display.oled;

void RFIDScannedNotf::paint() {
    paintNotfBox("Tag RFID Escaneado", content.msg);
    btnLabels[1] = "Cancelar " + timeLeft;
    paintNotfBtns(btnLabels, focusedBtn);
}

void RFIDScannedNotf::onInput(Button& button) {
    if (button.pin == state.input.pins.MID && focusedBtn == 0) state.display.notifications.remove(this);
    if (button.pin == state.input.pins.LFT) moveCursor(-1);
    if (button.pin == state.input.pins.RGT) moveCursor(1);
}