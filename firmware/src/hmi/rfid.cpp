#include "rfid.h"
#include "buzzer.h" // Include buzzer.h to use playTone

// Define RFID-related constants
#define SS_PIN 5   // ESP32 pin GIOP4 (HSPI SS)
#define RST_PIN 22 // ESP32 pin GIOP21 (arbitrary)

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setupRFID(RfidPins pins)
{
    Serial.println("setupRFID");
    SPI.begin();        // Init SPI bus, setupRFID
    mfrc522.PCD_Init(); // Init MFRC522 card

    Serial.println("Approximate reader attributes:");
    mfrc522.PCD_DumpVersionToSerial();
}

void runRFID()
{
    // Look for new cards
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
        Serial.print(F("PICC type: "));
        MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.println(mfrc522.PICC_GetTypeName(piccType));

        // Check if see if blockKeyA matches the card's blockKeyA
        Serial.print("Card UID: ");
        String content = "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        content.toUpperCase();

        // Play a success sound
        playTone(1000, 100); // Play a 1000 Hz tone for 100ms

        // Halt PICC
        mfrc522.PICC_HaltA();

        // Stop encryption on PCD
        mfrc522.PCD_StopCrypto1();
    } // End of new card present
}