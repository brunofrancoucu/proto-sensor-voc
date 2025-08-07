#include "ui/dashboards.h"
#include "core/state.h"

ScanView scanView;

void ScanView::paint() {
    // none
}

void ScanView::onInput(Button& button) {
    // No specific actions needed on entering the scan view
    state.display.navTo(&menuView);
}