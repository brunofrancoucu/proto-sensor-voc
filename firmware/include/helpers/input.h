#ifndef INPUT_H
#define INPUT_H

#include "core/state.h"
#include "hmi/buttons.h"

void updateButton(Button& button, std::function<void()> callback);

#endif
 