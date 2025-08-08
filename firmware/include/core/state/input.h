#ifndef STATE_INPUT_H
#define STATE_INPUT_H
#include <Arduino.h>
#include "hmi/buttons.h" // ButtonPins
#include <vector>

// Constants for long press detection and repeat interval
const unsigned long LONG_PRESS_THRESHOLD = 300; // milliseconds
const unsigned long REPEAT_INTERVAL_SUBSEQUENT = 200;

class Button {
private:
public:
    uint8_t pin;
    // Button down state
    bool pressed = false;
    // Used once in current cycle
    bool once = false;
    // Accelerate on hold
    unsigned long interval_ms = 400;
    unsigned long prev_ms = 0;
    unsigned long hold_ms = 0;
    /*
    * Enable internal pull-up resistor:
    * This keeps the input HIGH when not pressed
    * Button should connect pin to GND when pressed (reads LOW).
    */
    explicit Button(uint8_t pin) : pin(pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    /** @brief Update global state properties (pressed & down_ms)
     * @note Lasts at least 1 cycle (toggle press back)
     * Workflow: pressed event within module / comp (gamified) onPress
    */
    void onPress(std::function<void()> callback) {
        bool pressed = !digitalRead(pin);
        // Update state.input.<btn> props
        pressed = pressed;
        if (pressed) {
            if (prev_ms == 0) { // First press
                prev_ms = millis();
                once = false;
                
                callback();
            } else { 
                // Holding down
                unsigned long diff_ms = millis() - prev_ms;
                prev_ms = millis();
                hold_ms += diff_ms;
                
                if (hold_ms > LONG_PRESS_THRESHOLD + interval_ms ) {
                    hold_ms -= interval_ms;
                    interval_ms = interval_ms/1.1; // Faster repeat interval
                    
                    callback();
                }
            }
        } else {
            interval_ms = REPEAT_INTERVAL_SUBSEQUENT;
            prev_ms = 0;
            hold_ms = 0;
            once = false;
        }
    }
};

struct InputState {
    std::vector<Button> buttons;    
    ButtonPins pins;
};

#endif // STATE_INPUT_H