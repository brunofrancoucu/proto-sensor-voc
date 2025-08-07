#include "ui/components.h"
#include "ui/dashboards.h"
#include "core/state.h" // view.h

static auto& oled = state.display.oled;

void dashboard::paint() {
    // state.btns.L = "SUBIR"
    switch (state.display.activeOpt) {
        case 0: // Sensors
            sensorsView.paint();
        break;
        case 1: // Scan
            sensorsView.paint();
        break;
        case 2: // Brightness
            state.display.content.btmbarTxtL = "BAJAR";
            state.display.content.btmbarTxtR = "SUBIR";
            brightnessView.paint();
            break;
        case 3: // Volume
            state.display.content.btmbarTxtL = "BAJAR";
            state.display.content.btmbarTxtR = "SUBIR";
            volumeView.paint();
            break;
            case 4: // Hotspot
            state.display.content.btmbarTxtL = "INFO";
            state.display.content.btmbarTxtR = "";
            hotspotView.paint();
        break;
    }
}