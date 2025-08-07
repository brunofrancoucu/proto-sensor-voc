#include "ui/components.h"
#include "ui/screens.h"
#include "core/state.h"

static auto& oled = state.display.oled;

void dashboard::paint() {
    // state.btns.L = "SUBIR"
    switch (state.display.activeOpt) {
        case 0: // Sensors
            sensors::paint({
            .temp = state.air.temp,
            .hum = state.air.hum
        });
        break;
        case 1: // Scan
            sensors::paint({
            .temp = 22,
            .hum = 33
        });
        break;
        case 2: // Vol Bright
            settings::paint({
                .volume = state.system.volume,
                .brightness = state.display.brightness
            });
        break;
        case 3: // Connect
            hotspot::paint({
                .SSID = state.hotspot.SSID,
                ._PWD = state.hotspot._PWD
            });
        break;
        case 4: // Volume
        //   sensors::paint({
        //   .temp = String(22),
        //   .hum = String(33)
        // });
        break;
    }
}