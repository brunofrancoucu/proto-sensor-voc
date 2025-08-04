#ifndef FORMAT_H
#define FORMAT_H

#include <Arduino.h>

void printHex(byte *buffer, byte bufferSize);
void printDec(byte *buffer, byte bufferSize);
String msToClock(unsigned long millis, int gmt = -3);

#endif
 