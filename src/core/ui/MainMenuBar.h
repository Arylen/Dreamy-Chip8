#pragma once

#include "core/AppState.h"
#include "core/ui/UiElement.h"

namespace dc8::core::ui {
    class MainMenuBar : public UiElement {
    public:
        MainMenuBar(AppState& state);
        void drawUi() override;
    };
}
