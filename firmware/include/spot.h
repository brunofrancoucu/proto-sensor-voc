#ifndef SPOT_H
#define SPOT_H

struct SpotConfig
{
    String SSID;
    String PWD;
};

void setupSpot(SpotConfig config);
void runSpot();

#endif
