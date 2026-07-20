#include "Application.h"
#include "core/AppState.h"
#include "core/ui/MainMenuBar.h"

namespace dc8 {
    Application::Application() {
        state_ = core::AppState{};
        uiElements_.push_back(std::make_unique<core::ui::MainMenuBar>(state_));
    }

    void Application::update(float dt) {

    }

    void Application::draw() {

    }

    void Application::drawUi() {
        for (auto& e : uiElements_) {
            e->drawUi();
        }
    }
}
