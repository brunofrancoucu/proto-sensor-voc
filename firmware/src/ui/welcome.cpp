#include "ui/instances.h"
#include "core/state.h"

static const unsigned char PROGMEM image_plant_bits[] = {0x00,0x03,0x00,0x0f,0x20,0x1f,0x70,0x3f,0xf8,0x3f,0xfc,0x7e,0xfc,0x7e,0xfc,0x7c,0x78,0xf0,0x30,0xc0,0x10,0x80,0x08,0x80,0x05,0x00,0x03,0x00,0x01,0x00,0x01,0x00};

static auto& oled = state.display.oled;

WelcomeView welcomeView;

void WelcomeView::paint () {    
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(50, 1);
    // plant
    oled.drawBitmap(56, 24, image_plant_bits, 16, 16, 1);
}

void WelcomeView::onInput(Button& button) {
    // No specific actions needed on entering the welcome view
    state.display.navTo(&menuView);
}