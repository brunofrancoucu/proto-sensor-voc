#ifndef STATE_DISPLAY_H
#define STATE_DISPLAY_H
#include <vector>
#include <Arduino.h>

enum UIMode {
    Navigation,
    Dashboard,
    /** Notification pop up with options */
    Notification
};

/** Components state, can be changed within UI (contents) */
struct Content {
    const std::vector<std::string> labels = {"Sensores", "Medir", "Ajustes", "Conectar", "Volumen"};
    std::string btmbarTxtL;
    std::string btmbarTxtR;
};

struct UIState
{
    UIMode mode = UIMode::Navigation;
    Content content;
    int activeOpt = 0; // VIEW
    int focusedOpt = 0; // hovered selection
    std::vector<int> matrix = std::vector<int>(5, 0);

    void next(int maxOptions = 5) {
        focusedOpt = (focusedOpt + 1) % maxOptions;
    }
    
    void prev(int maxOptions = 5) {
        focusedOpt = (focusedOpt - 1 + maxOptions) % maxOptions;
    }

    void select() {
        // Store updated adjustment state
        matrix[activeOpt] = focusedOpt;

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
            mode = UIMode::Navigation;
            // Update Navigation Content
            content.btmbarTxtL = content.labels[(activeOpt + content.labels.size() - 1) % (content.labels.size())];
            content.btmbarTxtR = content.labels[(activeOpt + content.labels.size() + 1) % (content.labels.size())];
            break;
        case UIMode::Notification:
            mode = UIMode::Navigation;
        default:
            break;
        }
    }

    bool isOn;
    int brightness = 128; // 0-255
};

#endif // STATE_DISPLAY_H