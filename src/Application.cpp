#include "Application.h"
#include "core/ui/UiHost.h"
#include <memory>

namespace dc8 {
    Application::Application() {
        uiHost_ = std::make_unique<core::ui::UiHost>(state_);
    }

    Application::~Application() {

    }

    void Application::update(float deltaTime) {
        uiHost_->update(deltaTime);
    }

    void Application::draw() {
        uiHost_->draw();
    }

    void Application::drawUi() {
        uiHost_->drawUi();
    }
}
