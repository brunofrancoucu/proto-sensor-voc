#ifndef STATE_DISPLAY_H
#define STATE_DISPLAY_H
#include <vector>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "ui/interfaces.h"

#define SSD_WIDTH 128
#define SSD_HEIGHT 64

/** @brief Components state, can be changed within UI (contents) */
struct UIState {
    // Initializes (same reference at aliases)
    Adafruit_SSD1306 oled{SSD_WIDTH, SSD_HEIGHT, &Wire, -1};
    // erase-remove idiom (single pass)
    std::vector<Notification*> notifications;
    std::weak_ptr<std::vector<std::shared_ptr<Notification>>> notifications = std::make_shared<std::vector<std::shared_ptr<Notification>>>();
    View* activeView;

    // Enter dashboard, view nav
    void navTo(View* view) {
        view->enter();
        activeView = view;
    }
    
    /** @brief Reduce brightness via contrast
     * @note Adafruit_SSD1306 lib no public contrast()
     * @param value 0x00 (dimmest) to 0xFF (brightest), try 0x40 for lower brightness
     */
    void setBrightness(uint8_t value) {
        oled.ssd1306_command(SSD1306_SETCONTRAST);
        oled.ssd1306_command(value);
    }

    // void addNotification(std::shared_ptr<Notification> notification) {
    //     if (auto nots = notifications.lock()) {
    //         nots->push_back(notification);
            
    //         // Set the self-container reference for self-removal
    //         notification->selfContainer = nots;
    //     }
    // }
};

#endif // STATE_DISPLAY_H