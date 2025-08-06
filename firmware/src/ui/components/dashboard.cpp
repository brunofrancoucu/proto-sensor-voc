#include "ui/components.h"
#include "ui/screens.h"
#include "state.h"

void dashboard::paint(Adafruit_SSD1306& oled) {
    // state.btns.L = "SUBIR"
    switch (state.display.activeOpt) {
        case 0: // Sensors
            sensors::paint(oled, {
            .temp = static_cast<int>(state.air.temp),
            .hum = static_cast<int>(state.air.hum)
        });
        break;
        case 1: // Scan
            sensors::paint(oled, {
            .temp = static_cast<int>(22),
            .hum = static_cast<int>(33)
        });
        break;
        case 2: // Vol Bright
        //    sensors::paint(oled, {
        //     .temp = static_cast<int>(22),
        //     .hum = static_cast<int>(33)
        // });
        break;
        case 3: // Connect
            hotspot::paint(oled, {
                .SSID = std::string(state.hotspot.SSID.c_str()),
                ._PWD = std::string(state.hotspot._PWD.c_str())
            });
        break;
        case 4: // Volume
        //   sensors::paint(oled, {
        //   .temp = static_cast<int>(22),
        //   .hum = static_cast<int>(33)
        // });
        break;
    }
}