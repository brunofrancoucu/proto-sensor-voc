#ifndef SCREENS_H
#define SCREENS_H

#include <Adafruit_SSD1306.h>

// Screens (Adjustment views, Welcome)

namespace welcome {
    void paint(Adafruit_SSD1306& oled);
};

namespace sensors {
    struct Config {
        int temp;
        int hum;
    };

    void paint(Adafruit_SSD1306& oled, Config config);
}

namespace hotspot {
    struct Config {
        std::string SSID;
        std::string _PWD;
    };

    void paint(Adafruit_SSD1306& oled, Config config);
}

#endif // SCREENS_H