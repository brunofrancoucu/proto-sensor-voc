#ifndef STATE_H
#define STATE_H
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
    UIMode mode;
    Content content;
    int activeOpt; // VIEW
    int focusedOpt; // hovered selection
    std::vector<int> matrix;

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
    int brightness;
};

struct InputButton
{
    // Button down state
    bool pressed = false;
    // Used once in current cycle
    bool once = false;
    // Accelerate on hold
    unsigned long interval_ms = 400;
    unsigned long prev_ms = 0;
    unsigned long hold_ms = 0;
};

struct InputState
{
    InputButton LFT;
    InputButton MID;
    InputButton RGT;
};

// Settings (vol)

struct AirState
{
    float temp;
    float hum;
    float mq2;
    float mq135;
    String status;
    // measure method
};

struct ScanState
{
    int motorSpeed; // on off, relay
    bool isRunning;
};

struct Hotspot {
    String SSID;
    String _PWD;
    bool isRunning;
};

struct AppState
{
    UIState display;
    ScanState scan;
    AirState air;
    InputState input;
    Hotspot hotspot;
};

extern AppState state;

#endif
