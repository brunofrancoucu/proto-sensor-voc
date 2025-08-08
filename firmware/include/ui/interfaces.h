#pragma once
/* This file contains interface (abstract) classes used across the UI. */
#include <Arduino.h>
#include "hmi/buttons.h"
#include "core/state/input.h"

/** @brief Crude interface element abstract class (NO INPUT), along views.
 * Components are reusable UI elements that can be used in different views.
*/
template<typename ContentType = void>
class Interface {
public:
    /** @brief Components content state (labels icons), 
     * @note enables change within UI (contents) 
    */
    ContentType content;
    /** @brief Paint the view content on the display */
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

/**
 * @brief Base abstract class for all views in the UI (Input handling).
 * @note Handling custom event callbacks for button presses.
 * Each view implement (default to navTo(menu)).
 */
class View : public Interface<> {
public:
    String label;
    const unsigned char* icon;

    View() : label(""), icon(nullptr) {}  // Default constructor
    View(const String& viewLabel, const unsigned char* viewIcon)  // ✅ Parameterized constructor
    : label(viewLabel), icon(viewIcon) {}
    
    /** @brief Called when the view is entered 
     * @note setup dependencies, ex btmbar
     */
    virtual void enter() {}
    
    /** @brief Handle input events (button presses)
     * @param button The button that was pressed (pin)
     * @note Default to navTo(menuView)
     */
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};