#include "MainMenuBar.h"
#include "core/AppState.h"
#include "core/ui/UiElement.h"
#include "imgui.h"

namespace dc8::core::ui {
    MainMenuBar::MainMenuBar(AppState& state): UiElement(state) {

    }

    void MainMenuBar::drawUi() {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open ROM", nullptr, &state_.showLog)) {

            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Logs", nullptr, &state_.showLog);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
