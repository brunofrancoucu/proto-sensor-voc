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
    struct Config {
        std::vector<std::string> labels;
        int focused;
    };

    void paint(Adafruit_SSD1306& oled, Config config);
}

// Handle active screen (ref. screens.h)
namespace screen {
    struct Config {
        int active;
    };
    
    void paint(Adafruit_SSD1306& oled, Config config);
}

// Atom Components (Stat)

void paintStatBox(Adafruit_SSD1306& oled, const unsigned char* icon, const String& txt, int x, int y);

#endif