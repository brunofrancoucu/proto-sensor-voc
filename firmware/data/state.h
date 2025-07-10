#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

struct AppState
{
    int motorSpeed;
    float temperature;
    float humidity;
    String air;
    bool isRunning;
};

extern AppState state;

#endif
