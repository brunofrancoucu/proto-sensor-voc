#include "cycle.h"

// not redeclared class, methods, keept method implementations

CycleEvery::CycleEvery(unsigned long interval) : lastTime(0), interval(interval) {}

void CycleEvery::run(std::function<void()> callback) {
    unsigned long now = millis();
    if (now - lastTime >= interval) {
        lastTime = now;
        callback();
    }
}