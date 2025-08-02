#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

struct ScreenState {
    bool isOn;
    int brightness;
    // interface
    int view;
};

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
    ScreenState screen;
    ScanState scan;
    AirState air;
};

extern AppState state;

#endif
