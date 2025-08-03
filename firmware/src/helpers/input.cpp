#include "helpers/input.h"

/** @brief Update global state properties (pressed & down_ms)
 * @note Lasts at least 1 cycle (toggle press back)
 */
void updateButton(uint8_t pin, InputButton& button) {
    bool pressed = !digitalRead(pin);    
    // Update state.input.<btn> props
    button.pressed = pressed;
    if (pressed) {
        button.down_ms = millis();
    } else {
        button.down_ms = 0;
    }
}