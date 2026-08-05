#include "CpuStateWindow.h"
#include "core/ui/UiElement.h"
#include "imgui.h"

namespace dc8::core::ui::windows {
    CpuStateWindow::CpuStateWindow(AppState& state) : UiElement(state) {

    }

    void CpuStateWindow::drawUi() {
        drawCpuReg();
        drawVReg();
        drawStack();
    }

    void CpuStateWindow::drawCpuReg() {
        if (ImGui::Begin("CPU Register")) {
            ImGui::Text("PC: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getPc());
            ImGui::Text(" I: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getI());
            ImGui::Text("DT: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getDelayTimer());
            ImGui::Text("ST: "); ImGui::SameLine(); ImGui::Text("%04X", state_.vm.getSoundTimer());
            ImGui::Separator();
            ImGui::Text("CYC: "); ImGui::SameLine(); ImGui::Text("%d", state_.vm.getCycleCount());
        }
        ImGui::End();
    }

    void CpuStateWindow::drawVReg() {
        if (ImGui::Begin("Gen Registers")) {
            for (int i = 0; i < 8; i++) {
                ImGui::Text("V%01X: ", i); ImGui::SameLine(); ImGui::Text("%02X", state_.vm.getV(i));
                ImGui::SameLine(); ImGui::Text("  "); ImGui::SameLine();
                ImGui::Text("V%01X: ", i + 8); ImGui::SameLine(); ImGui::Text("%02X", state_.vm.getV(i + 8));
            }
        }
        ImGui::End();
    }

    void CpuStateWindow::drawStack() {
        if (ImGui::Begin("Stack")) {
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
