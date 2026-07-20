#pragma once

#include "core/AppState.h"
namespace dc8::core::ui {
    class UiElement {
    public:
        UiElement(AppState& state) : state_(state) {}
        virtual ~UiElement() = default;
        virtual void drawUi() = 0;
    protected:
        AppState& state_;
    };
}
