#include "Application.h"

namespace dc8 {
    Application::Application() {

    }

    void Application::drawUi() {
        for (auto& e : uiElements_) {
            e.drawUi();
        }
    }
}
