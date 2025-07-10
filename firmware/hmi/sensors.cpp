#include <DHT.h>

#include "sensors.h"
#include "data/state.h"

String calidad;
DHT *dht = nullptr; // dht pointer
uint8_t mqPin = 0;

void setupSensors(uint8_t pinMQ, uint8_t pinDHT)
{
    mqPin = pinMQ;
    if (dht)
        delete dht; // Clean up if already allocated
    dht = new DHT(pinDHT, DHT11);
    dht->begin();
}

void runSensors()
{
    // Safety check
    if (!dht)
    {
        Serial.print("DHT Error");
        return;
    }

    float temp = dht->readTemperature();
    float hum = dht->readHumidity();
    int mq_raw = analogRead(mqPin);

    // Normalize values
    float mq_volt = mq_raw * (3.3 / 4095.0); // ADC de 12 bits
    calidad = (mq_volt < 0.5) ? "Buena" : (mq_volt < 1.0) ? "Regular"
                                                          : "Mala";

    // Serial monitor (Temp / Hum / MQ / Aire)
    Serial.println("Temp: " + String(temp) + " C | Hum: " + String(hum) + " %");
    Serial.println("MQ: " + String(mq_volt) + " V | Aire: " + calidad);

    // Update global state
    state.temperature = temp;
    state.humidity = hum;
    state.air = calidad;
    // state.air = mq_volt;
}