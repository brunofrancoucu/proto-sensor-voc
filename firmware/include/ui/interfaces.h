#pragma once
/* This file contains interface (abstract) classes used across the UI. */
#include <Arduino.h>
#include <memory>
#include <vector>
#include "hmi/buttons.h"
#include "core/state/input.h"

/** @brief Crude polymorphic interface element abstract class (NO INPUT).
 * Components are reusable UI elements that can be used in different views.
*/
template<typename ContentType = void>
class Interface {
public:
    Interface(ContentType content) : content(content) {}
    // @brief Components content state (labels icons), 
    // @note enables change within UI (contents) 
    ContentType content;
    // @brief Paint the view content on the display
    virtual void paint() = 0;
    virtual ~Interface() {}
};
// Specialization
template<>
class Interface<void> {
    public:
    virtual void paint() = 0;
    virtual ~Interface() {}
};

struct ViewContent { String label; const unsigned char* icon; };
/**
 * @brief Base abstract class for all views in the UI (Input handling).
 * @note Handling custom event callbacks for button presses.
 * Each view implement (default to navTo(menu)).
 */
class View : public Interface<ViewContent> {
public:
    View(const String& viewLabel, const unsigned char* viewIcon)
    : Interface<ViewContent>({viewLabel, viewIcon}) {}
    // @brief Called when the view is entered
    // @note setup dependencies, ex btmbar
    virtual void enter() {}
    // @brief Handle input events (button presses)
    // @param button The button that was pressed (pin)
    // @note Default to navTo(menuView)
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};

struct NotContent { String msg; };
/**
 * @brief Notification interface for UI components (self-managed).
 * @note Stacked in state, priority should override onInput.
 */
class Notification : public Interface<NotContent> {
public:
    Notification(const NotContent& content, std::vector<String> labels) 
    : Interface<NotContent>({content}), btnLabels(labels) { 
        created_ms = millis();
        moveCursor(0);
     }
    virtual void onInput(Button& button) = 0;
    uint16_t duration_ms = 4000; // ms
    uint16_t created_ms; // Constructor initialized
    String timeLeft;
    int focusedBtn = 0; // Focused Btn
    std::vector<String> btnLabels = {"Ok"}; // Btns
    // Update button labels with remaining time self remove
    void update();
    /** @brief Move menu nav cursor left/right */
    void moveCursor(int direction);
};