#include "ui/molecules.h"
#include "core/state.h"
#include "helpers/blink.h"

static auto& oled = state.display.oled;

// Stats Dashboard

/**
 * @brief Molecule Component, Statistic Module
*/
void paintStatBox(const unsigned char* icon, const String& txt, int x, int y) {    
    oled.drawBitmap(x, y, icon, 13, 14, 1);
    oled.setCursor(x + 18, y + 4);
    oled.print(txt);
}

// Settings Dual

static Blink unused;

void paintSettingBox(bool isSelected, bool isActive, const unsigned char* icon, String text, int x, int y)
{
    const int txtWidth = 24;
    oled.drawBitmap(x + 6, y + 6, icon, 20, 16, 1);
    oled.setCursor(x + 6 + 4 + 20, y + 6 + 4);
    blinkIf(isActive, unused, [&](){ oled.print(text); }, 0);

    if (isSelected) {
        oled.drawRoundRect(x, y, 62, 26, 7, 1);
    }
}

// Setting single

void paintSetting(const unsigned char* icon, String text, float iconRatio) {
    oled.drawBitmap(16, 16, icon, 32 * iconRatio, 32, 1);
    oled.setTextSize(2);
    oled.setCursor(66, 25);
    oled.print(text);
    
    // Reset
    oled.setTextSize(1);
}