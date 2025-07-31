#ifndef CYCLE_H
#define CYCLE_H

#include <functional>
#include <Arduino.h>

/**
 * Analog voltage that gluctuates. Analog to digital conversion, waste CPU cycles.
 * Noisy sensor readings, compute average over time. Warm-up (MQ sensors).
 * TODO hmi ui ap to Class run & setup
 */
class CycleEvery {
    unsigned long lastTime;
    unsigned long interval;

public:
    CycleEvery(unsigned long interval);
    void run(std::function<void()> callback);
};

#endif