#include "state.h"

AppState state = {
    .display = {
        .mode = UIMode::Navigation,
        .activeOpt = 0,
        .focusedOpt = 0,
        .matrix = std::vector<int>(5, 0),
        .isOn = false,
        .brightness = 128,
    },
    .scan = {
        .motorSpeed = 0,
        .isRunning = false
    },
    .air = {
        .temp = 25.0f,
        .hum = 50.0f,
        .mq2 = 0.0f,
        .mq135 = 0.0f,
        .status = "..."
    }
};