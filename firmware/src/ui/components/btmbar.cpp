#include "ui/components.h"
#include "core/state.h"

static const unsigned char PROGMEM image_ButtonLeft_bits[] = {0x10,0x30,0x70,0xf0,0x70,0x30,0x10};
static const unsigned char PROGMEM image_ButtonRight_bits[] = {0x80,0xc0,0xe0,0xf0,0xe0,0xc0,0x80};
static const unsigned char PROGMEM image_Ok_btn_bits[] = {0x3e,0x00,0x41,0x00,0x9c,0x80,0xbe,0x80,0xbe,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00};

static const unsigned long gap = 2;
static const unsigned long iconsWidth = 9 + 3*2 + 4*2;

static auto& oled = state.display.oled;

void btmbar::paint(Config config) {
    // Align Center txt to slot L
    int16_t x1, y1;
    uint16_t wL, h1;
    oled.getTextBounds(config.txtL, 0, 0, &x1, &y1, &wL, &h1);
    const uint8_t iconsLeftX = (SSD_WIDTH - iconsWidth)/2 - gap;
    // Layer 13 copy
    oled.setCursor(iconsLeftX/2 - wL/2, 56);
    oled.print(config.txtL);

    // Align Center txt R to slot 
    int16_t x2, y2;
    uint16_t wR, h2;
    oled.getTextBounds(config.txtR, 0, 0, &x2, &y2, &wR, &h2);
    const uint8_t iconsRightX = (SSD_WIDTH + iconsWidth)/2 + gap * 2;
    // Layer 13
    oled.setCursor(iconsRightX + (SSD_WIDTH - iconsRightX)/2 - wR/2, 56);
    oled.print(config.txtR);
    
    // Ok_btn
    oled.drawBitmap(60, 55, image_Ok_btn_bits, 9, 9, 1);
    // ButtonLeft
    oled.drawBitmap(53, 56, image_ButtonLeft_bits, 4, 7, 1);
    // ButtonRight
    oled.drawBitmap(72, 56, image_ButtonRight_bits, 4, 7, 1);
    // Layer 2 copy
    oled.drawLine(-1, 52, 127, 52, 1);
}