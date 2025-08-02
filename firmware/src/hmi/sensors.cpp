#include "drivers/sensors.h"
#include <DHT.h>
// Internal
#include "state.h"

namespace {
    String calidad;
    DHT *dht = nullptr; // dht pointer
    uint8_t mqPin = 0;

    void initSetup(SensorsPins pins)
    {
        mqPin = pins.MQ;
        dht = new DHT(pins.DHT, DHT11);
        dht->begin();
    }
    
    void cycle()
    {
        float temp_raw = dht->readTemperature();
        float hum_raw = dht->readHumidity();
        int mq_raw = analogRead(mqPin);
    
        // Normalize values
        float mq_volt = mq_raw * (3.3 / 4095.0); // ADC de 12 bits
        calidad = (mq_volt < 0.5) ? "Buena" : (mq_volt < 1.0) ? "Regular"
                                                              : "Mala";
    
        // Serial monitor (Temp / Hum / MQ / Aire)
        Serial.println("Temp: " + String(temp_raw) + " C | Hum: " + String(hum_raw) + " %");
        Serial.println("MQ: " + String(mq_volt) + " V | Aire: " + calidad);

        if (isnan(state.air.temp) && isnan(state.air.hum))
        {
            // Update global state
            state.air.temp = temp_raw;
            state.air.hum = hum_raw;
            state.air.status = calidad;
            // state.air = mq_volt;
        }
        state.air.mq2 = mq_raw;
    }
}

// Export
decltype(sensors) sensors = makeCycleComp(initSetup, cycle);
