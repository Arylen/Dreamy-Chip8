#pragma once

#include "core/ui/UiElement.h"

namespace dc8::core::ui::windows {
    class QuickCtrlWindow : public UiElement {
    public:
        QuickCtrlWindow(AppState& state);
        void drawUi() override;
    };
}
