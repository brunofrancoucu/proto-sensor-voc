#include "ui/interfaces.h"
#include "ui/instances.h"
#include "core/state.h"
#include "core/state/display.h"

void Notification::update() {
    timeLeft = String((duration_ms - (millis() - created_ms) + 300) / 1000);
    if (millis() - created_ms >= duration_ms) state.display.notifications.remove(this);
}

void Notification::moveCursor(int direction) {
    focusedBtn = (focusedBtn + direction + btnLabels.size()) % btnLabels.size();
    // Update state btmbar labels
    btmbar.content.txtL = btnLabels[(focusedBtn + btnLabels.size() - 1) % (btnLabels.size())];
    btmbar.content.txtR = btnLabels[(focusedBtn + 1) % (btnLabels.size())];
}

// State/display header implementation
void NotificationManager::remove(Notification* notification) {
    auto it = std::remove_if(_notifications.begin(), _notifications.end(),
        [notification](const std::shared_ptr<Notification>& ptr) { return ptr.get() == notification; }
    );
    if (it != _notifications.end()) _notifications.erase(it, _notifications.end());
    state.display.activeView->enter(); // Re-enter active view
}