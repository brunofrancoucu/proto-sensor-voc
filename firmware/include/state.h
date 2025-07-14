#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

// struct SensorReadings {
//   float temperature;
//   String air;
// };

// struct AppState {
//   int motorSpeed;
//   SensorReadings readings; // Object as a property
//   bool isRunning;
// };

struct AppState
{
    int motorSpeed;
    float temperature;
    float humidity;
    float mq_raw;
    String air;
    bool isRunning;
};

extern AppState state;

#endif
