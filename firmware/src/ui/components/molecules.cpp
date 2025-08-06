#include "ui/molecules.h"

/**
 * @brief Molecule Component, Statistic Module
*/
void paintStatBox(Adafruit_SSD1306& oled, const unsigned char* icon, const String& txt, int x, int y) {
    oled.drawBitmap(x, y, icon, 13, 14, 1);
    oled.setCursor(x + 18, y + 4);
    oled.print(txt);
}
