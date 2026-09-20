#include "QuickCtrlWindow.h"

#include "imgui.h"

namespace dc8::core::ui::windows {
    QuickCtrlWindow::QuickCtrlWindow(AppState& state) : UiElement(state) { }
    void QuickCtrlWindow::drawUi() {
        if (!state_.showQuickControls) {
            return;
        }

        if (ImGui::Begin("Quick Controls")) {
            // Auto-size the controls n shit.
            int amountOfButtons = 4;
            float spacing = ImGui::GetStyle().ItemSpacing.x;
            float width = (ImGui::GetContentRegionAvail().x - spacing * (amountOfButtons - 1)) / amountOfButtons;
            ImVec2 size (width, 0);

            // TODO: Toggle between Play / Pause whenever VM state gets added.
            ImGui::Button("Play", size); ImGui::SameLine();
            ImGui::Button("Reset", size); ImGui::SameLine();
            ImGui::Button("Step", size);
        }

        ImGui::End();
    }
}
