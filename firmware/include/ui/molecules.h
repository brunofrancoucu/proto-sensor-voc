#ifndef MOLECULES_H
#define MOLECULES_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//  module/paintStat
void paintStatBox(Adafruit_SSD1306& oled, const unsigned char* icon, const String& txt, int x, int y);

#endif
