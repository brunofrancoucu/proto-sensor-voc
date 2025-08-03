#include "state.h"

AppState state = {
    .display = {
        .isOn = false,
        .brightness = 128,
        .view = 0
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