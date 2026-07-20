#pragma once

#include "core/AppState.h"
#include "core/ui/UiElement.h"

#include <vector>

namespace dc8 {
    class Application {
    public:
        Application();
        void update(float dt);
        void draw();
        void drawUi();
    private:
        core::AppState state_;
        std::vector<std::unique_ptr<core::ui::UiElement>> uiElements_;
    };
}
