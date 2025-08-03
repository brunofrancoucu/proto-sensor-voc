#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

enum class UIMode {
    Navigation,
    Adjustment,
    NotPopUp
};

struct DisplayState {
    bool isOn;
    int brightness;
    // interface
    int view;
    UIMode mode = UIMode::Navigation;

    void next(int maxViews = 3) {
        view = (view + 1) % maxViews;
    }

    void prev(int maxViews = 3) {
        view = (view - 1 + maxViews) % maxViews;
    }
};

struct InputButton {
    bool pressed = false;
    bool usedOnce = false;
    unsigned long down_ms = 0;
};

struct InputState {
    InputButton LFT;
    InputButton MID;
    InputButton RGT;
};

// Settings (vol)

struct AirState {
  float temp;
  float hum;
  float mq2;
  float mq135;
  String status;
};

struct ScanState {
    int motorSpeed; // on off, relay
    bool isRunning;
};

struct AppState
{
    DisplayState display;
    ScanState scan;
    AirState air;
    InputState input;
};

extern AppState state;

#endif
