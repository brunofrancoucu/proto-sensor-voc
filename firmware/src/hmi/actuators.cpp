#include "drivers/actuators.h"
#include <DHT.h>

namespace {
    bool active = false;           // Your target variable
    unsigned long activeUntil = 0; // Time until which active stays true
    uint8_t relPin = 0;
    uint8_t pushPin = 0;

    void initSetup(ActuatorPins pins)
    {
        relPin = pins.REL;
        pushPin = pins.BTN;
        pinMode(pins.REL, OUTPUT);
        digitalWrite(pins.REL, LOW);     // Relay OFF if active-low
        pinMode(pins.BTN, INPUT_PULLUP); // Internal pull-up resistor
    }
    
    void cycle()
    {
        static bool lastButtonState = HIGH;
        bool buttonState = digitalRead(pushPin);
    
        // Detect falling edge (button press)
        if (lastButtonState == HIGH && buttonState == LOW)
        {
            active = true;
            activeUntil = millis() + 10000; // 10 seconds from now
            Serial.println("Button pressed, active set to true");
        }
        lastButtonState = buttonState;
    
        // If 10 seconds passed, reset active
        if (active && millis() > activeUntil)
        {
            active = false;
            Serial.println("10 seconds passed, active set to false");
        }
    
        if (active)
        {
            Serial.print("Motor ON");
            digitalWrite(relPin, HIGH); // Turn on relay (active-low)
        }
        else
        {
            Serial.print("Motor OFF");
            digitalWrite(relPin, LOW); // Turn off relay (active-low)
        }
    }
}

decltype(actuators) actuators = makeCycleComp(initSetup, cycle);