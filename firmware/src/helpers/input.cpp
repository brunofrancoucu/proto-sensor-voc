#include "helpers/input.h"
#include "core/state/input.h"

// Constants for long press detection and repeat interval
const unsigned long LONG_PRESS_THRESHOLD2 = 300; // milliseconds
const unsigned long REPEAT_INTERVAL_SUBSEQUENT2 = 200;

/** @brief Update global state properties (pressed & down_ms)
 * @note Lasts at least 1 cycle (toggle press back)
 */
void updateButton(Button& button, std::function<void()> callback) {
    bool pressed = !digitalRead(button.pin);
    // Update state.input.<btn> props
    button.pressed = pressed;
    if (pressed) {
        if (button.prev_ms == 0) { // First press
            button.prev_ms = millis();
            button.once = false;
            
            callback();
        } else { 
            // Holding down
            unsigned long diff_ms = millis() - button.prev_ms;
            button.prev_ms = millis();
            button.hold_ms += diff_ms;
            
            if (button.hold_ms > LONG_PRESS_THRESHOLD2 + button.interval_ms ) {
                button.hold_ms -= button.interval_ms;
                button.interval_ms = button.interval_ms/1.1; // Faster repeat interval
                
                callback();
            }
        }
    } else {
        button.interval_ms = REPEAT_INTERVAL_SUBSEQUENT2;
        button.prev_ms = 0;
        button.hold_ms = 0;
        button.once = false;
    }
}