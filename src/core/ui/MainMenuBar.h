#pragma once

#include "core/AppState.h"
#include "core/Entity.h"
namespace dc8::core::ui {
    class MainMenuBar : public Entity {
    public:
        MainMenuBar(AppState& state);
        ~MainMenuBar();
        void update(float deltaTime);
        void drawUi();
        void draw();
    private:
        AppState& state_;
    };
}
