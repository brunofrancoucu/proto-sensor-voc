#ifndef SENSORS_H
#define SENSORS_H

struct SensorPins
{
    uint8_t MQ;
    uint8_t DHT;
};

void setupSensors(SensorPins pins);
void runSensors();

#endif