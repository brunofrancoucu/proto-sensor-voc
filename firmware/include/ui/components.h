#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <Adafruit_SSD1306.h>
#include <vector>

// Welcome

namespace welcome {
    void paint(Adafruit_SSD1306& oled);
};

// UI Components for the display

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

// Adjustment Views

namespace sensors {
    struct Config {
        int temp;
        int hum;
    };

    void paint(Adafruit_SSD1306& oled, Config config);
}

#endif