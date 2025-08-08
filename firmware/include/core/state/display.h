#ifndef STATE_DISPLAY_H
#define STATE_DISPLAY_H
#include <vector>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "ui/interfaces.h"

#define SSD_WIDTH 128
#define SSD_HEIGHT 64

/** @brief Centralizes all notifications management displayed on the screen */
class NotificationManager {
public:
    size_t size() const { return _notifications.size(); }
    // Handle all
    void paint() { for (auto& notification : _notifications) notification->paint(), notification->update(); }
    // Handle input for all notifications
    void onInput(Button& button) { for (auto& notification : _notifications) notification->onInput(button); }
    void add(Notification* notification) {_notifications.push_back(std::shared_ptr<Notification>(notification));}
    void remove(Notification* notification);
private:
    std::vector<std::shared_ptr<Notification>> _notifications; // dangling pointers
};

/** @brief Components state, can be changed within UI (contents) */
struct UIState {
    // Initializes (same reference at aliases)
    Adafruit_SSD1306 oled{SSD_WIDTH, SSD_HEIGHT, &Wire, -1};
    // erase-remove idiom (single pass)
    NotificationManager notifications = NotificationManager();
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
};

#endif // STATE_DISPLAY_H