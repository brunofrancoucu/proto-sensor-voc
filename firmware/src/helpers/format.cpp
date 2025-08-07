#include "helpers/format.h"

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

#define GMT -3 // GMT offset in hours, adjust as needed

/**
 * @brief Transform millis() into clock time format (HH:MM).
 * @param millis Time in milliseconds.
 * @note gmt GMT hours from macro
 */
String msToClock(unsigned long millis) {
  unsigned long totalSeconds = millis / 1000;
  unsigned long hours = (totalSeconds / 3600 + GMT) % 24; // Wrap around after 24 hours
  unsigned long minutes = (totalSeconds / 60) % 60;

  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%02lu:%02lu", hours, minutes);
  return String(buffer);
}