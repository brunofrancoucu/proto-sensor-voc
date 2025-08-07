#include "helpers/blink.h"

/** @brief Custom blink effect for icons.
 * @note (defaults to no blink, ON).
 */
void blinkIf(bool condition, Blink& state, std::function<void()> drawCb, unsigned long offset) {
    if (condition) {
        ((millis() + offset) % 600 < 200) && (drawCb(), 0); // 200ms on 400ms off
    } else {
        drawCb();
    }
}