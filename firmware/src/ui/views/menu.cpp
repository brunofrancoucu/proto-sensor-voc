#include "ui/instances.h"
// Navigation menu
#include "core/state.h"

static const std::vector<View*> views = {
    &sensorsView,
    &scanView,
    &brightnessView,
    &volumeView,
    &hotspotView,
};

static auto& oled = state.display.oled;

MenuView menuView("", nullptr);
static int focusedId = 0;

/** @brief Move menu nav cursor left/right */
void moveCursor(int direction, int maxOptions = 5) {
    focusedId = (focusedId + direction + maxOptions) % maxOptions;
    // Update navigation bar text
    btmbar.content.txtL = views[(focusedId + views.size() - 1) % (views.size())]->label;
    btmbar.content.txtR = views[(focusedId + views.size() + 1) % (views.size())]->label;
}

void MenuView::paint() {
    // Selected
    int16_t x1, y1;
    uint16_t w, h;
    oled.getTextBounds(views[focusedId]->label, 0, 0, &x1, &y1, &w, &h);
    // Draw
    const uint8_t gap = 8;
    const uint8_t pdg = 8;
    const uint8_t rectWidth = 16 + w + gap + pdg*2; // txt + gap + padding
    oled.drawRoundRect((SSD_WIDTH - rectWidth)/2, 19, rectWidth, 24, 7, 1); // h: 24 => 64/2 - h/2
    oled.drawBitmap((SSD_WIDTH - rectWidth)/2 + pdg, 23, views[focusedId]->icon, 16, 16, 1);
    oled.setCursor((SSD_WIDTH - rectWidth)/2 + 16 + gap + pdg, 27); // 64/2 - 8/2
    oled.print(views[focusedId]->label);
    
    // Icons Left
    for (size_t i = 0; i < views.size(); ++i) {
        int posX = SSD_WIDTH / 2 - rectWidth / 2 - i * (16 + 10) - 8 - 16;
        oled.drawBitmap(posX, 23, views[(focusedId - i - 1 + views.size()) % views.size()]->icon, 16, 16, 1);
    }
    
    // Icons Right
    for (size_t i = 0; i < views.size(); ++i) {
        int posX = SSD_WIDTH / 2 + rectWidth / 2 + i * (16 + 10) + 8;
        oled.drawBitmap(posX, 23, views[(focusedId + i + 1) % views.size()]->icon, 16, 16, 1);
    }
}

void MenuView::onInput(Button& button) {
    if (button.pin == state.input.pins.LFT) {
        // LFT();
        moveCursor(-1);
    } else if (button.pin == state.input.pins.MID) {
        // MID();
        state.display.navTo(views[focusedId]);
    } else if (button.pin == state.input.pins.RGT) {
        // RGT();
        moveCursor(1);
    }
}
