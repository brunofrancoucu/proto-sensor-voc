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

namespace brightness {
    void paint();
}

namespace volume {
    void paint();
}

#endif // SCREENS_H