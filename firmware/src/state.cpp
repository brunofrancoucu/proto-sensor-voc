#include "state.h"

AppState state = {
    .motorSpeed = 0,
    .temperature = 2,
    .humidity = 32,
    .mq_raw = 0,
    .air = "...",
    // .readings = {0.0, "..."}, // Initialize the SensorReadings object
    .isRunning = false};
