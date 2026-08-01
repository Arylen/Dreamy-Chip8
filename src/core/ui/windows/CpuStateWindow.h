#pragma once

#include "core/ui/UiElement.h"

namespace dc8::core::ui::windows {
    class CpuStateWindow : public UiElement {
    public:
        CpuStateWindow(AppState& state);
        void drawUi() override;
    };
}
