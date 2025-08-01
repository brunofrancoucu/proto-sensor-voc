#include "rfid.h"
#include <SPI.h>
#include <MFRC522.h>
// Internal
#include "buzzer.h"
#include "format.h"

namespace {
  MFRC522* mfrcid = nullptr;
  MFRC522::MIFARE_Key key; 
  byte nuidPICC[4]; // store new NUID 
  
  void initSetup(RfidPins pins) {
    mfrcid = new MFRC522(pins.SDA, pins.RST);
    SPI.begin(pins.SCK, pins.MISO, pins.MOSI, pins.SDA); // SPI bus
    mfrcid->PCD_Init(); // Init MFRC522 
  
    for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF; // Defailt MIFARE classic
    }
  }
   
  void cycle() {
    if (mfrcid == nullptr) return;
      if ( ! mfrcid->PICC_IsNewCardPresent())
      return;
    if ( ! mfrcid->PICC_ReadCardSerial()) // NUID read
      return;
  
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrcid->PICC_GetType(mfrcid->uid.sak);
    Serial.println(mfrcid->PICC_GetTypeName(piccType));
  
    // Check is the PICC of Classic MIFARE type
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && 
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      Serial.println(F("Your tag is not of type MIFARE Classic."));
      return;
    }
  
    if (mfrcid->uid.uidByte[0] != nuidPICC[0] || 
      mfrcid->uid.uidByte[1] != nuidPICC[1] || 
      mfrcid->uid.uidByte[2] != nuidPICC[2] || 
      mfrcid->uid.uidByte[3] != nuidPICC[3] ) {
      Serial.println(F("A new card has been detected."));
  
      // Store NUID into nuidPICC array
      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = mfrcid->uid.uidByte[i];
      }
     
      Serial.println(F("The NUID tag is:"));
      Serial.print(F("In hex: "));
      printHex(mfrcid->uid.uidByte, mfrcid->uid.size);
      Serial.println();
      Serial.print(F("In dec: "));
      printDec(mfrcid->uid.uidByte, mfrcid->uid.size);
      Serial.println();
  
      // Play a success sound
      playTone(1000, 100); // Play a 1000 Hz tone for 100ms
    }
    else Serial.println(F("Card read previously."));
  
    // Halt PICC
    mfrcid->PICC_HaltA();
  
    // Stop encryption on PCD
    mfrcid->PCD_StopCrypto1();
  }
}

// Export
decltype(rfid) rfid = makeCycleComp(initSetup, cycle);