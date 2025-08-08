#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
#include "ui/interfaces.h"

// Macros to declare a view class and its instance

#define DECLARE_INTERFACE(ClassName, declName, ContentType) \
    class ClassName : public Interface<ContentType> { \
    public: \
        void paint() override; \
        ClassName(ContentType content) : Interface<ContentType>(content) {} \
    }; \
    extern ClassName declName; \

#define DECLARE_SIMPLE_INTERFACE(ClassName, declName) \
    class ClassName : public Interface<> { \
    public: \
        void paint() override; \
        ClassName() {} \
    }; \
    extern ClassName declName;

#define DECLARE_VIEW(ClassName, declName) \
    class ClassName : public View { \
    public: \
        ClassName(const String& label, const unsigned char* icon) \
            : View(label, icon) {} \
        void paint() override; \
        void enter() override; \
        void onInput(Button& button) override; \
    }; \
    extern ClassName declName; \
    
#define DECLARE_NOTIFICATION(ClassName) \
    class ClassName : public Notification { \
    public: \
        ClassName(const NotContent& content, std::vector<String> labels) \
        : Notification(content, labels) {} \
        void paint() override; \
        void onInput(Button& button) override; \
    }; \

// Declarations instances of interfaces

DECLARE_SIMPLE_INTERFACE(WelcomeView, welcomeView)
// Views
DECLARE_VIEW(BrightnessView, brightnessView)
DECLARE_VIEW(VolumeView, volumeView)
DECLARE_VIEW(ScanView, scanView)
DECLARE_VIEW(SensorsView, sensorsView)
DECLARE_VIEW(HotspotView, hotspotView)
DECLARE_VIEW(MenuView, menuView)

struct BtmBarConfig {
    String txtL;
    String txtR;
};

DECLARE_SIMPLE_INTERFACE(NavBar, navbar)
DECLARE_INTERFACE(BtmBar, btmbar, BtmBarConfig)
// Notifications
DECLARE_NOTIFICATION(RFIDScannedNotf)


#undef DECLARE_INTERFACE
#undef DECLARE_VIEW
#endif // SCREENS_H