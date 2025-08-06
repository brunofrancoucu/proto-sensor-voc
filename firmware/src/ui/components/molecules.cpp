#include "ui/molecules.h"
#include "core/state.h"

static auto& oled = state.display.oled;

/**
 * @brief Molecule Component, Statistic Module
*/
void paintStatBox(const unsigned char* icon, const String& txt, int x, int y) {    
    oled.drawBitmap(x, y, icon, 13, 14, 1);
    oled.setCursor(x + 18, y + 4);
    oled.print(txt);
}
