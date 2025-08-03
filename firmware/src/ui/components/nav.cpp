#include "ui/components.h"

static const unsigned char PROGMEM image_ButtonLeft_bits[] = {0x10,0x30,0x70,0xf0,0x70,0x30,0x10};

static const unsigned char PROGMEM image_ButtonRight_bits[] = {0x80,0xc0,0xe0,0xf0,0xe0,0xc0,0x80};

static const unsigned char PROGMEM image_Ok_btn_bits[] = {0x3e,0x00,0x41,0x00,0x9c,0x80,0xbe,0x80,0xbe,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00};

namespace nav {
    void paint(Adafruit_SSD1306& oled) {
        // Ok_btn
        oled.drawBitmap(60, 55, image_Ok_btn_bits, 9, 9, 1);

        // ButtonLeft
        oled.drawBitmap(53, 56, image_ButtonLeft_bits, 4, 7, 1);

        // ButtonRight
        oled.drawBitmap(72, 56, image_ButtonRight_bits, 4, 7, 1);

        // Layer 2 copy
        oled.drawLine(-1, 52, 127, 52, 1);

        // Layer 13
        oled.setTextColor(1);
        oled.setTextWrap(false);
        oled.setCursor(81, 56);
        oled.print("SUBIR");

        // Layer 13 copy
        oled.setCursor(19, 56);
        oled.print("BAJAR");

        oled.display();
    };
}