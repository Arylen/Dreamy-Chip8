#include "CpuStateWindow.h"
#include "core/ui/UiElement.h"
#include "imgui.h"

namespace dc8::core::ui::windows {
    CpuStateWindow::CpuStateWindow(AppState& state) : UiElement(state) {

    }

    void CpuStateWindow::drawUi() {
        if (ImGui::Begin("CPU State")) {
            ImGui::Text("PC: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getPc());
            ImGui::Text(" I: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getI());
            ImGui::Text("DT: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getDelayTimer());
            ImGui::Text("ST: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getSoundTimer());
            ImGui::Text("CYCLES: "); ImGui::SameLine(); ImGui::Text(state_.vm.getCycleCount());
        }

        ImGui::End();
    }
}
