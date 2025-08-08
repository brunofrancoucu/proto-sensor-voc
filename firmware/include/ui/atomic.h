#ifndef MOLECULES_H
#define MOLECULES_H

#include <string>
#include <Arduino.h>
#include <vector>

/** module/paintStat */
void paintStatBox(const unsigned char* icon, const String& txt, int x, int y);

/** Dual settings */
void paintSettingBox(bool isSelected, bool isActive, const unsigned char* icon, String text, int x, int y);

/** Single setting (full screen) */
void paintSetting(const unsigned char* icon, String text, float iconRatio = 1.0f);

/** Notification box */
void paintNotfBox(String line1, String line2);
void paintNotfBtn(const String& label, int x, bool isFocused);
void paintNotfBtns(std::vector<String> labels, int focusedBtn);

#endif
