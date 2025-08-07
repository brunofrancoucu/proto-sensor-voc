#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <vector>
#include <Arduino.h>

// UI Layout Components for the display

namespace navbar {
    struct Icon {
        bool show;
        bool blink;
    };

    struct Config {
        String clock;
        Icon alert;
        Icon ap;
        Icon wifi;
        Icon bat;
    };

    void paint(Config config);
}

namespace btmbar {
    struct Config {
        String txtL;
        String txtR;
    };

    void paint(Config config);
}

namespace menu {
    void paint();
}

namespace dashboard {
    void paint();
}

// Atom Components (Stat)

void paintStatBox(const unsigned char* icon, const String& txt, int x, int y);

#endif