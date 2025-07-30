#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Structure to hold RFID pin numbers
struct RfidPins
{
    uint8_t SDA;
    uint8_t SCK;
    uint8_t MOSI;
    uint8_t MISO;
    uint8_t RST;
};

void setupRFID(RfidPins pins);
void runRFID();

// Function declarations
void printHex(byte *buffer, byte bufferSize);
void printDec(byte *buffer, byte bufferSize);
 
#endif