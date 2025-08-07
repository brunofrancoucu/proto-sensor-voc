#ifndef STATE_H
#define STATE_H
#include <vector>
#include <Arduino.h>

#include "core/state/display.h"
#include "core/state/input.h"

// Settings (vol)

struct AirState
{
    float temp = 25.0f;
    float hum = 50.0f;
    float mq2 = 0.0f;
    float mq135 = 0.0f;
    String status = "...";
    // measure method
};

struct ScanState
{
    int motorSpeed = 0; // on off, relay
    bool isRunning = false;
};

struct HotspotState {
    String SSID;
    String _PWD;
    bool isRunning;
};

// Others..
struct System {
    int volume = 50; // 0-100
    String clock = "00:00"; // HH:MM
    int battery = 80; // 0-100
};

struct AppState
{
    UIState display;
    ScanState scan; // TODO: merge into air
    AirState air;
    InputState input;
    HotspotState hotspot;
    System system;
};

extern AppState state;

#endif
