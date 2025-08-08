#include "ui/atomic.h"
#include "core/state.h"
#include "helpers/blink.h"
#include "helpers/oled.h"
#include <vector>

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

void paintNotfBox(String line1, String line2 = "") {
    // Notification Border Background fill
    oled.fillRect(3, 12, 122, 38, 0);
    oled.drawRect(4, 12, 121, 37, 1);

    // Line 1 (title)
    uint16_t l1w = txtWidth(line1);
    // center if no 2
    int l1y = line2.length() > 0 ? 15 : 20; 
    oled.setCursor((oled.width()-l1w)/2 +1, l1y);
    oled.print(line1);
    // Line 2
    uint16_t l2w = txtWidth(line2);
    oled.setCursor((oled.width()-l2w)/2 +1, 25);
    oled.print(line2);
}

void paintNotfBtn(const String& label, int x, bool isFocused) {
    uint16_t w = txtWidth(label);
    // Btn box
    oled.setTextColor(isFocused ? 0 : 1); // Invert text color
    oled.fillRoundRect(x - 4 + 1, 37 - 2 + 1, w + 8 - 2, 12 - 2, 0, isFocused ? 1 : 0);
    // Text
    oled.setCursor(x, 37);
    oled.print(label);
    oled.setTextColor(1); // Reset text color
}

// Paint notification buttons
void paintNotfBtns(std::vector<String> labels, int focusedBtn) {
    for (size_t i = 0; i < labels.size(); i++) {
        const String& btnLab = labels[i];
        uint16_t w = btnWidth(btnLab);
        int btnsLftWd = 0;
        int btnsRgtWd = 0;
        for (size_t j = 0; j < labels.size(); j++) {
            if (j < i) btnsLftWd += btnWidth(labels[j]) + 4; // 4px gap
            if (j > i) btnsRgtWd += btnWidth(labels[j]) + 4; // 4px gap
        }
        int x = (oled.width() - w - btnsRgtWd + btnsLftWd) / 2 + 1;

        paintNotfBtn(btnLab, x, focusedBtn == i);
    }
}