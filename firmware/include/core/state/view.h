#pragma once
#include "hmi/buttons.h"
#include "core/state/input.h"

// Abstract screen interface
class View {
public:
    virtual void paint() = 0;
    virtual void onInput(Button& button) = 0;
    virtual ~View() {}
};