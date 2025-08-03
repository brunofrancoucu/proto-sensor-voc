#include "ui/buzzer.h"

int duty = 4;

void playTone(int freq, int duration)
{
    ledcWriteTone(0, freq); // Set frequency
    ledcWrite(0, duty);     // Set volume
    delay(duration);
    ledcWrite(0, 0); // Stop tone
    delay(30);       // Small pause between notes
}

namespace {
    void initSetup(BuzzerPins pins)
    {
    
        // Initialize the buzzer pin
        pinMode(pins.BZR, OUTPUT);
        // Set up LEDC for PWM control of the buzzer
        ledcSetup(0, 2000, 8);      // (channel, frequency, resolution)
        ledcAttachPin(pins.BZR, 0); // Attach buzzerPin to channel 0
        duty = pins.VOL;            // Set volume (0-255)
    
        // Welcome sound
        playTone(523, 100); // C5 (do)
        playTone(659, 100); // E5 (mi)
        playTone(784, 150); // G5 (sol)
    }
    
    void cycle()
    {
    }
}

decltype(buzzer) buzzer = makeCycleComp(initSetup, cycle);
