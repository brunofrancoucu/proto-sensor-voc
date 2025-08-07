#include "ui/dashboards.h"
// Navigation menu
#include "core/state.h"

static const unsigned char PROGMEM image_menu_settings_gear_bits[] = {0x03,0xc0,0x12,0x48,0x2c,0x34,0x40,0x02,0x23,0xc4,0x24,0x24,0xc8,0x13,0x88,0x11,0x88,0x11,0xc8,0x13,0x24,0x24,0x23,0xc4,0x40,0x02,0x2c,0x34,0x12,0x48,0x03,0xc0};
static const unsigned char PROGMEM image_monitor_bits[] = {0x00,0x00,0xff,0xff,0x80,0x01,0xbf,0xfd,0xa0,0x05,0xa0,0x05,0xa0,0x05,0xa0,0x05,0xa0,0x05,0xbf,0xfd,0x80,0x01,0xff,0xff,0x03,0xc0,0x03,0xc0,0x0f,0xf0,0x00,0x00};
static const unsigned char PROGMEM image_music_radio_broadcast_bits[] = {0x07,0xc0,0x18,0x30,0x27,0xc8,0x48,0x24,0x93,0x92,0xa4,0x4a,0xa9,0x2a,0xa3,0x8a,0x06,0xc0,0x03,0x80,0x01,0x00,0x03,0x80,0x02,0x80,0x06,0xc0,0x04,0x40,0x00,0x00};
static const unsigned char PROGMEM image_volume_custom[] = {0x01,0xc0,0x02,0x40,0x04,0x48,0x08,0x44,0xf0,0x42,0x80,0x52,0x80,0x49,0x80,0x49,0x80,0x49,0x80,0x52,0xf0,0x42,0x08,0x44,0x04,0x48,0x02,0x40,0x01,0xc0,0x00,0x00};
static const unsigned char PROGMEM image_weather_windsock_bits[] = {0x00,0x00,0x80,0x00,0xcf,0x00,0xb6,0xf0,0xab,0x68,0xab,0x68,0x97,0xf0,0x9c,0x00,0xa0,0x00,0xc0,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00};
static const unsigned char PROGMEM image_display_brightness_bits[] = {0x01,0x00,0x21,0x08,0x10,0x10,0x03,0x80,0x8c,0x62,0x48,0x24,0x10,0x10,0x10,0x10,0x10,0x10,0x48,0x24,0x8c,0x62,0x03,0x80,0x10,0x10,0x21,0x08,0x01,0x00,0x00,0x00};


static const std::vector<const unsigned char*> icons = {
    image_monitor_bits, // Stats
    image_weather_windsock_bits, // Measure
    image_display_brightness_bits, // Brightness
    image_volume_custom, // Volume
    image_music_radio_broadcast_bits, // Communicate
};

static const std::vector<View*> views = {
    &sensorsView,
    &scanView,
    &brightnessView,
    &volumeView,
    &hotspotView,
};

// Reference aliases
static auto& oled = state.display.oled;
static const std::vector<String>& labels = state.display.content.labels;
static const int& foc = state.display.focusedOpt;
// Interface constants
static const uint8_t iconWidth = 16;

MenuView menuView;

void MenuView::paint() {
    // Selected
    int16_t x1, y1;
    uint16_t w, h;
    oled.getTextBounds(labels[foc], 0, 0, &x1, &y1, &w, &h);
    // Draw
    const uint8_t gap = 8;
    const uint8_t pdg = 8;
    const uint8_t rectWidth = iconWidth + w + gap + pdg*2; // txt + gap + padding
    oled.drawRoundRect((SSD_WIDTH - rectWidth)/2, 19, rectWidth, 24, 7, 1); // h: 24 => 64/2 - h/2
    oled.drawBitmap((SSD_WIDTH - rectWidth)/2 + pdg, 23, icons[foc], 16, 16, 1);
    oled.setCursor((SSD_WIDTH - rectWidth)/2 + iconWidth + gap + pdg, 27); // 64/2 - 8/2
    oled.print(labels[foc]);
    
    // Icons Left
    for (size_t i = 0; i < labels.size(); ++i) {
        int posX = SSD_WIDTH / 2 - rectWidth / 2 - i * (iconWidth + 10) - 8 - iconWidth;
        oled.drawBitmap(posX, 23, icons[(foc - i - 1 + labels.size()) % labels.size()], 16, 16, 1);
    }
    
    // Icons Right
    for (size_t i = 0; i < labels.size(); ++i) {
        int posX = SSD_WIDTH / 2 + rectWidth / 2 + i * (iconWidth + 10) + 8;
        oled.drawBitmap(posX, 23, icons[(foc + i + 1) % labels.size()], 16, 16, 1);
    }
}

// Navigation direction
enum Nav { NEXT = 1, PREV = -1 };

void moveCursor(Nav direction, int maxOptions = 5) {
    int& focusedOpt = state.display.focusedOpt;
    focusedOpt = (focusedOpt + direction + maxOptions) % maxOptions;
    // Update navigation bar text
    state.display.content.btmbarTxtL = state.display.content.labels[(focusedOpt + state.display.content.labels.size() - 1) % (state.display.content.labels.size())];
    state.display.content.btmbarTxtR = state.display.content.labels[(focusedOpt + state.display.content.labels.size() + 1) % (state.display.content.labels.size())];
}

void MenuView::onInput(Button& button) {
    if (button.pin == state.input.pins.LFT) {
        // LFT();
        moveCursor(Nav::PREV);
    } else if (button.pin == state.input.pins.MID) {
        // MID();
        state.display.navTo(views[foc]);
    } else if (button.pin == state.input.pins.RGT) {
        // RGT();
        moveCursor(Nav::NEXT);
    }
}
