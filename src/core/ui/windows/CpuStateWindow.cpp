#include "CpuStateWindow.h"
#include "core/ui/UiElement.h"
#include "imgui.h"

namespace dc8::core::ui::windows {
    CpuStateWindow::CpuStateWindow(AppState& state) : UiElement(state) {

    }

    void CpuStateWindow::drawUi() {
        if (ImGui::Begin("CPU State")) {
            ImGui::Text("PC: "); ImGui::SameLine(); ImGui::Text("%X4", state_.vm.getPc());
        }

        ImGui::End();
    }
}
