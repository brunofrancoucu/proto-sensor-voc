#include "state.h"

AppState state = {
    .motorSpeed = 0,
    .temperature = 0.0,
    .air = "...",
    // .readings = {0.0, "..."}, // Initialize the SensorReadings object
    .isRunning = false};
