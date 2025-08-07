#ifndef STATE_DISPLAY_H
#define STATE_DISPLAY_H
#include <vector>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "core/state/view.h"

#define SSD_WIDTH 128
#define SSD_HEIGHT 64

// enum UIMode {
//     Navigation,
//     Dashboard,
//     /** Notification pop up with options */
//     Notification
// };

/** Components state, can be changed within UI (contents) */
struct Content {
    const std::vector<String> labels = {"Sensores", "Medir", "Brillo", "Volumen", "Conectar"};
    String btmbarTxtL = labels[labels.size() - 1];
    String btmbarTxtR = labels[0];
};


struct UIState {
    Adafruit_SSD1306 oled{SSD_WIDTH, SSD_HEIGHT, &Wire, -1}; // Initialize (same reference at aliases)
    Content content;
    // Interaction
    // UIMode mode = UIMode::Navigation;
    View* activeView;

    // Enter dashboard
    void navTo(View* view) {
        activeView = view;
        // // Store updated adjustment state
        // matrix[activeOpt] = focusedOpt;
        // int prevActive = matrix[focusedOpt];

        // // Internal state options
        // activeOpt = focusedOpt;
        // focusedOpt = matrix[focusedOpt]; // enter adj val
    }
    
    /** @brief Reduce brightness via contrast
     * @note Adafruit_SSD1306 lib no public contrast()
     * @param value 0x00 (dimmest) to 0xFF (brightest), try 0x40 for lower brightness
     */
    void setBrightness(uint8_t value) {
        // brightness = max(min(value, uint8_t(254)), uint8_t(1));
        oled.ssd1306_command(SSD1306_SETCONTRAST);
        oled.ssd1306_command(value);
    }
};

#endif // STATE_DISPLAY_H