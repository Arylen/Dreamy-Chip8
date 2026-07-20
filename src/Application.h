#pragma once

#include "core/Entity.h"
#include "core/AppState.h"
#include <memory>

namespace dc8 {
    class Application : public core::Entity {
    public:
        Application();
        ~Application();
        void update(float deltaTime);
        void draw();
        void drawUi();
    private:
        core::AppState state_;
        std::unique_ptr<Entity> uiHost_;
        std::unique_ptr<Entity> emulatorHost_;
    };
}
