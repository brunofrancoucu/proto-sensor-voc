#ifndef STATE_INPUT_H
#define STATE_INPUT_H
#include <Arduino.h>

struct InputButton {
    // Button down state
    bool pressed = false;
    // Used once in current cycle
    bool once = false;
    // Accelerate on hold
    unsigned long interval_ms = 400;
    unsigned long prev_ms = 0;
    unsigned long hold_ms = 0;
};

struct InputState {
    InputButton LFT;
    InputButton MID;
    InputButton RGT;

    // TODO: action
};

#endif // STATE_INPUT_H