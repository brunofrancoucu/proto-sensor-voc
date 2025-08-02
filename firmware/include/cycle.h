#ifndef CYCLE_H
#define CYCLE_H

#include <functional>
#include <Arduino.h>

/**
 * @brief A periodic task scheduler with optional setup logic.
 * @note Use at components, sensors or routines that need warm-up/setup and periodic execution.
 * alt: Using a Class with Virtual Functions (C++ OO style)
 * @see makeCycleComp
 */
template<typename... Args>
class CycleComp {
  unsigned long prev_ms = 0;

private:
  std::function<void(Args...)> setupCallback;
  std::function<void()> runCallback;

public:
  CycleComp(std::function<void(Args...)> sCb,  std::function<void()> rCb)
    : setupCallback(sCb), runCallback(rCb) {}

  void setup(Args... args) {
    return setupCallback(std::forward<Args>(args)...);
  }

  // Non blocking periodic execution
  void run(unsigned long period_ms = 100) {
    if (millis() - prev_ms >= period_ms) {
      // Cumulative delay correction (keep allignment)
      int drift_ms = (millis() - prev_ms - period_ms) % period_ms;
      prev_ms = millis() - drift_ms;
      if (runCallback) runCallback();
    }
  }
};

/**
 * @copybrief CycleComp - type safe factory
 * @note For function pointers (support lambda via twice pointer in params)
 * @see CycleComp
 */
template<typename Ret, typename... Args>
auto makeCycleComp(Ret (*sCb)(Args...), std::function<void()> rCb) -> CycleComp<Args...> {
    return CycleComp<Args...>(sCb, rCb);
}

#endif // CYCLE_H
