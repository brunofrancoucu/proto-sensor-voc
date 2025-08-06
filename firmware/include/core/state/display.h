#ifndef STATE_DISPLAY_H
#define STATE_DISPLAY_H
#include <vector>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

enum UIMode {
    Navigation,
    Dashboard,
    /** Notification pop up with options */
    Notification
};

/** Components state, can be changed within UI (contents) */
struct Content {
    const std::vector<String> labels = {"Sensores", "Medir", "Ajustes", "Conectar", "Volumen"};
    String btmbarTxtL = labels[labels.size() - 1];
    String btmbarTxtR = labels[0];
};

// Navigation direction
enum Nav { NEXT = 1, PREV = -1 };

struct UIState {
    Adafruit_SSD1306 oled{128, 64, &Wire, -1}; // Initialize (same reference at aliases)
    Content content;
    // Interaction
    UIMode mode = UIMode::Navigation;
    int activeOpt = 0; // VIEW
    int focusedOpt = 0; // hovered selection
    std::vector<int> matrix = std::vector<int>(5, 0);
    // Config
    bool isOn;
    uint8_t brightness = 128; // 0-255

    // Assumes mode is Navigation
    void nav(Nav dir, int maxOptions = 5) {
        focusedOpt = (focusedOpt + dir + maxOptions) % maxOptions;
        // Update navigation bar text
        content.btmbarTxtL = content.labels[(focusedOpt + content.labels.size() - 1) % (content.labels.size())];
        content.btmbarTxtR = content.labels[(focusedOpt + content.labels.size() + 1) % (content.labels.size())];
    }

    // Enter dashboard
    void select() {
        // Store updated adjustment state
        matrix[activeOpt] = focusedOpt;
        int prevActive = matrix[focusedOpt];

        // Internal state options
        activeOpt = focusedOpt;
        focusedOpt = matrix[focusedOpt]; // enter adj val

        // Interface View
        switch (mode)
        {
        case UIMode::Navigation:
            /* code */
            mode = UIMode::Dashboard;
            break;

        case UIMode::Dashboard:
            /* code */
            focusedOpt = prevActive;
            mode = UIMode::Navigation;
            break;
        case UIMode::Notification:
            mode = UIMode::Navigation;
        default:
            break;
        }
    }
    
    /** @brief Reduce brightness via contrast
     * @note Adafruit_SSD1306 lib no public contrast()
     * @param value 0x00 (dimmest) to 0xFF (brightest), try 0x40 for lower brightness
     */
    void setBrightness(uint8_t value) {
        brightness = value;
        oled.ssd1306_command(SSD1306_SETCONTRAST);
        oled.ssd1306_command(brightness);
    }
};

#endif // STATE_DISPLAY_H