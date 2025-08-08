#include "helpers/oled.h"
#include "core/state.h"

static auto& oled = state.display.oled;

uint16_t txtWidth(const String& text) {
    // Get text bounds
    uint16_t w, h;
    int16_t x1, y1;
    oled.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}

uint16_t btnWidth(const String& text) {
    return txtWidth(text) + 8; // Add padding
}
