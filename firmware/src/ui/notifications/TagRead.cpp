#include "ui/instances.h"
#include "core/state.h"
#include "ui/atomic.h"

#include <vector>
#include <memory>

static auto& oled = state.display.oled;

void TagRead::paint() {
    paintNotfBox("Tomar muestra?", content.msg);
    btnLabels[1] = "No (" + timeLeft + "s)";
    paintNotfBtns(btnLabels, focusedBtn);
}

void TagRead::onInput(Button& button) {
    if (button.pin == state.input.pins.MID && focusedBtn == 1) state.display.notifications.remove(this);
    if (button.pin == state.input.pins.LFT) moveCursor(-1);
    if (button.pin == state.input.pins.RGT) moveCursor(1);
}