#include "CpuStateWindow.h"
#include "core/ui/UiElement.h"
#include "imgui.h"

namespace dc8::core::ui::windows {
    CpuStateWindow::CpuStateWindow(AppState& state) : UiElement(state) { }

    void CpuStateWindow::drawUi() {
        drawCpuRegs();
    }

    void CpuStateWindow::drawCpuRegs() {
        if (ImGui::Begin("CPU Register")) {
            ImGui::Text("Cycle: "); ImGui::SameLine(); ImGui::Text("%d", state_.vm.getCycleCount());

            ImGui::SeparatorText("Registers");

            ImGui::Text("PC: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getPc());
            ImGui::Text(" I: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getI());
            ImGui::Text("DT: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getDelayTimer());
            ImGui::Text("ST: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getSoundTimer());

            ImGui::SeparatorText("GP Registers");

            for (int i = 0; i < 8; i++) {
                ImGui::Text("V%01X: ", i); ImGui::SameLine(); ImGui::Text("%02X", state_.vm.getV(i));
                ImGui::SameLine(); ImGui::Text("  "); ImGui::SameLine();
                ImGui::Text("V%01X: ", i + 8); ImGui::SameLine(); ImGui::Text("%02X", state_.vm.getV(i + 8));
            }

            ImGui::SeparatorText("Stack");

            size_t stackSize = state_.vm.getStack().size();
            if (stackSize == 0) {
                ImGui::Text("STACK EMPTY");
            }

            for (size_t i = 0; i < stackSize; i++) {
                ImGui::Text("%zu : ", i);
                ImGui::SameLine();
                ImGui::Text("%04X", state_.vm.getStack().front());
            }
        }

        ImGui::End();
    }
}
