#pragma once
// Interface abstract elements
#include "hmi/buttons.h"
#include "core/state/input.h"

/**
 * @brief Base abstract class for all views in the UI.
 * @note Handling custom event callbacks for button presses.
 * Each view implement (default to navTo(menu)).
 */
class View {
public:
    virtual void paint() = 0;
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};

// Component