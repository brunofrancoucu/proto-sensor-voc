#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
#include "ui/interfaces.h"

// Interfaces
#define DECLARE_INTERFACE(ClassName, declName) \
    class ClassName : public Interface { \
    public: \
        void paint() override; \
        virtual ~ClassName() {} \
    }; \
    extern ClassName declName; \
   
// Macro to declare a view class and its instance
#define DECLARE_VIEW(ClassName, declName) \
    class ClassName : public View { \
    public: \
    String label; \
        const unsigned char* icon; \
        void paint() override; \
        void onInput(Button& button) override; \
        ClassName(const String& viewLabel, const unsigned char* viewIcon) \
        : label(viewLabel), icon(viewIcon) {} \
    }; \
    extern ClassName declName; \
    
DECLARE_INTERFACE(WelcomeView, welcomeView)

DECLARE_VIEW(BrightnessView, brightnessView)
DECLARE_VIEW(VolumeView, volumeView)
DECLARE_VIEW(ScanView, scanView)
DECLARE_VIEW(SensorsView, sensorsView)
DECLARE_VIEW(HotspotView, hotspotView)
DECLARE_VIEW(MenuView, menuView)

#undef DECLARE_INTERFACE
#undef DECLARE_VIEW
#endif // SCREENS_H