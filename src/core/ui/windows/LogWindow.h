#pragma once

#include "core/ui/UiElement.h"
namespace dc8::core::ui::windows {
    class LogWindow : public UiElement {
    public:
        LogWindow(AppState& state);
        void drawUi() override;
    };
}
