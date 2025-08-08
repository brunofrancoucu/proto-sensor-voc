#pragma once
// This file contains interface (abstract) classes used across the UI.
#include "hmi/buttons.h"
#include "core/state/input.h"

class Interface {
public:
    virtual void paint() = 0;
    virtual ~Interface() {}
};

/**
 * @brief Base abstract class for all views in the UI.
 * @note Handling custom event callbacks for button presses.
 * Each view implement (default to navTo(menu)).
 */
class View : public Interface {
public:
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};

// Component

class Component : public Interface {
public:
    virtual void onInput(Button& button) = 0;
    virtual ~Component() {}
};