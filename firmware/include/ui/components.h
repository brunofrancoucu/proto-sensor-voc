#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <Adafruit_SSD1306.h>
#include <vector>

// UI Layout Components for the display

namespace navbar {
    struct Icon {
        bool show;
        bool blink;
    };

    struct Config {
        std::string clock;
        Icon alert;
        Icon ap;
        Icon wifi;
        Icon bt;
    };
    
    void paint(Adafruit_SSD1306& oled, Config config);
}

namespace btmbar {
    struct Config {
        std::string txtL;
        std::string txtR;
    };

    void paint(Adafruit_SSD1306& oled, Config config);
}

namespace menu {
    void paint(Adafruit_SSD1306& oled);
}

namespace dashboard {    
    void paint(Adafruit_SSD1306& oled);
}

// Atom Components (Stat)

void paintStatBox(Adafruit_SSD1306& oled, const unsigned char* icon, const String& txt, int x, int y);

#endif