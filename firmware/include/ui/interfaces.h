#pragma once
/* This file contains interface (abstract) classes used across the UI. */
#include <Arduino.h>
#include "hmi/buttons.h"
#include "core/state/input.h"

/** @brief Crude interface element abstract class (NO INPUT) */
class Interface {
public:
    virtual void paint() = 0;
    virtual ~Interface() {}
};

/**
 * @brief Base abstract class for all views in the UI (Input handling).
 * @note Handling custom event callbacks for button presses.
 * Each view implement (default to navTo(menu)).
 */
class View : public Interface {
public:
    String label;
    const unsigned char* icon;
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};

// Component

/**
 * @brief Base abstract class for components in the UI.
 * Components are reusable UI elements that can be used in different views.
 * They can handle their own input events.
 */
class Component : public Interface {
public:
    virtual ~Component() {}
};