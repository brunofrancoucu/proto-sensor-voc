#include "ui/interfaces.h"
#include "ui/instances.h"
#include "core/state.h"

void Notification::update() {
    timeLeft = String((duration_ms - (millis() - created_ms)) / 1000);
    if (millis() - created_ms >= duration_ms) {
        state.display.activeView->enter(); // Re-enter active view
        state.display.notifications.remove(this);
    }
}

void Notification::moveCursor(int direction) {
    focusedBtn = (focusedBtn + direction + btnLabels.size()) % btnLabels.size();
    // Update state btmbar labels
    btmbar.content.txtL = btnLabels[(focusedBtn + btnLabels.size() - 1) % (btnLabels.size())];
    btmbar.content.txtR = btnLabels[(focusedBtn + 1) % (btnLabels.size())];
}