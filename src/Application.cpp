#include "Application.h"
#include "core/AppState.h"
#include "core/ui/MainMenuBar.h"
#include "core/ui/windows/LogWindow.h"
#include <memory>

namespace dc8 {
    Application::Application() {
        state_ = core::AppState{};

        // UI Elements
        uiElements_.push_back(std::make_unique<core::ui::MainMenuBar>(state_));

        // Windows
        uiElements_.push_back(std::make_unique<core::ui::windows::LogWindow>(state_));
    }

    void Application::update(float) {

    }

    void Application::draw() {

    }

    void Application::drawUi() {
        for (auto& e : uiElements_) {
            e->drawUi();
        }
    }
}
