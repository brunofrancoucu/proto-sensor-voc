#include "rfid.h"
#include "buzzer.h" // Include buzzer.h to use playTone

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 21
 
MFRC522 mfrcid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void setupRFID(RfidPins pins) {
  SPI.begin(pins.SCK, pins.MISO, pins.MOSI, SS_PIN); // Init SPI bus
  mfrcid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void runRFID() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrcid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! mfrcid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrcid.PICC_GetType(mfrcid.uid.sak);
  Serial.println(mfrcid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && 
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (mfrcid.uid.uidByte[0] != nuidPICC[0] || 
    mfrcid.uid.uidByte[1] != nuidPICC[1] || 
    mfrcid.uid.uidByte[2] != nuidPICC[2] || 
    mfrcid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = mfrcid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(mfrcid.uid.uidByte, mfrcid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(mfrcid.uid.uidByte, mfrcid.uid.size);
    Serial.println();

    // Play a success sound
    playTone(1000, 100); // Play a 1000 Hz tone for 100ms
  }
  else Serial.println(F("Card read previously."));

  // Halt PICC
  mfrcid.PICC_HaltA();

  // Stop encryption on PCD
  mfrcid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}