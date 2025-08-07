#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>

// Screens (Adjustment views, Welcome)

namespace welcome {
    void paint();
};

namespace sensors {
    struct Config {
        float temp;
        float hum;
    };

    void paint(Config config);
}

namespace hotspot {
    struct Config {
        String SSID;
        String _PWD;
    };

    void paint(Config config);
}

namespace settings {
    struct Config {
        int volume; // %
        int brightness; // %
    };
    void paint(Config config);
}

namespace volume {
    void paint();
}

#endif // SCREENS_H