#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <Adafruit_SSD1306.h>

namespace nav {
    void paint(Adafruit_SSD1306& oled);
}

namespace menu {
    void paint(Adafruit_SSD1306& oled);
}

namespace sensors {
    void paint(Adafruit_SSD1306& oled);
}

#endif