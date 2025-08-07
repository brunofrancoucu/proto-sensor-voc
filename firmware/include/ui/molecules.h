#ifndef MOLECULES_H
#define MOLECULES_H

#include <string>
#include <Arduino.h>

/** module/paintStat */
void paintStatBox(const unsigned char* icon, const String& txt, int x, int y);

/** Dual settings */
void paintSettingBox(bool isSelected, bool isActive, const unsigned char* icon, String text, int x, int y);

/** Single setting (full screen) */
void paintSetting(const unsigned char* icon, String text, float iconRatio = 1);

#endif
