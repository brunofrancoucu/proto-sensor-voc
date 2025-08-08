#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
#include "ui/interfaces.h"


// Macro to declare a view class and its instance
#define DECLARE_VIEW(ClassName, viewName) \
    class ClassName : public View { \
    public: \
        void paint() override; \
        void onInput(Button& button) override; \
    }; \
    extern ClassName viewName; \


DECLARE_VIEW(BrightnessView, brightnessView)
DECLARE_VIEW(VolumeView, volumeView)
DECLARE_VIEW(ScanView, scanView)
DECLARE_VIEW(SensorsView, sensorsView)
DECLARE_VIEW(HotspotView, hotspotView)
DECLARE_VIEW(MenuView, menuView)
DECLARE_VIEW(WelcomeView, welcomeView)

#undef DECLARE_VIEW
#endif // SCREENS_H