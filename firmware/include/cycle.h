#ifndef CYCLE_H
#define CYCLE_H

#include <functional>
#include <Arduino.h>

/**
 * CycleComp - A periodic task scheduler with optional setup logic.
 * Use at components, sensors or routines that need warm-up/setup and periodic execution.
 */

template<typename... Args>
class CycleComp {
  unsigned long lastRun = 0;
  unsigned long interval = 0;

private:
  std::function<void(Args...)> setupCallback;
  std::function<void()> runCallback;

public:
  CycleComp(std::function<void(Args...)> sCb,  std::function<void()> rCb)
    : setupCallback(sCb), runCallback(rCb) {}

  void setup(Args... args) {
    return setupCallback(std::forward<Args>(args)...);
  }

  void run(unsigned long ms = 100) {
    if (millis() - lastRun >= ms) {
      lastRun = millis();
      if (runCallback) runCallback();
    }
  }
};

// For function pointers (support lambda via twice pointer in params)
template<typename Ret, typename... Args>
auto makeCycleComp(Ret (*sCb)(Args...), std::function<void()> rCb) -> CycleComp<Args...> {
    return CycleComp<Args...>(sCb, rCb);
}

#endif // CYCLE_H
