#include "ui/instances.h"
#include "core/state.h"
#include "ui/atomic.h"

#include <vector>
#include <memory>

static auto& oled = state.display.oled;

void NewScanNotf::paint() {
    paintNotfBox("Tomar muestra?", "Lectura en: #1");
    btnLabels[1] = "No (" + timeLeft + "s)";
    paintNotfBtns(btnLabels, focusedBtn);
}

void NewScanNotf::onInput(Button& button) {
    if (button.pin == state.input.pins.MID && focusedBtn == 1) state.display.notifications.remove(this);
    if (button.pin == state.input.pins.LFT) moveCursor(-1);
    if (button.pin == state.input.pins.RGT) moveCursor(1);
}