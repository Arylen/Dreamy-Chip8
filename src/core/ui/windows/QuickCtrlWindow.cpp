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

            if (ImGui::Button(state_.vmIsPaused ? "Play" : "Pause", size)) {
                state_.vmIsPaused = !state_.vmIsPaused;
            }
            ImGui::SameLine();

            if (ImGui::Button("Reset", size)) {
                state_.vm.reset();
            }
            ImGui::SameLine();

            if (ImGui::Button("Step", size)) {
                state_.vm.cycle();
            }
        }

        ImGui::End();
    }
}
