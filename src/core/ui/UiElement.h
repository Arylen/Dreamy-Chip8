#pragma once

#include "core/AppState.h"
namespace dc8::core::ui {
    class UiElement {
    public:
        UiElement(AppState& state);
        void drawUi();
    private:
        AppState& state_;
    };
}
