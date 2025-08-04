#ifndef INPUT_H
#define INPUT_H

#include "state.h"

void updateButton(uint8_t pin, InputButton& button, std::function<void()> callback);

#endif
 