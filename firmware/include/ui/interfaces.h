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
    // Components state, can be changed within UI (contents)
    ContentType content;
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
    
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};