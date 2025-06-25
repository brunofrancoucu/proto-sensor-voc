#include <DHT.h>
#include "Vent.h"

bool active = false;           // Your target variable
unsigned long activeUntil = 0; // Time until which active stays true
uint8_t relPin = 0;
uint8_t pushPin = 0;

void setupVent(uint8_t pinRel, uint8_t pinPush)
{
    relPin = pinRel;
    pushPin = pinPush;
    pinMode(9, OUTPUT);
    pinMode(pinRel, OUTPUT);
    digitalWrite(pinRel, LOW);      // Relay OFF if active-low
    pinMode(pinPush, INPUT_PULLUP); // Internal pull-up resistor
}

void runVent()
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

    // (Optional) Do something based on `active`
    if (active)
    {
        // display.print("Motor ON");
        // display.println(" (10 sec)");
        digitalWrite(relPin, HIGH); // Turn on relay (active-low)
    }
    else
    {
        // display.print("Motor OFF");
        digitalWrite(relPin, LOW); // Turn off relay (active-low)
                                   // Your logic here, e.g., turn on LED or relay
    }
}
