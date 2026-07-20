#include "MainMenuBar.h"
#include "core/AppState.h"
#include "imgui.h"

namespace dc8::core::ui {
    MainMenuBar::MainMenuBar(AppState& state): state_(state) {

    }

    MainMenuBar::~MainMenuBar() {

    }

    void MainMenuBar::update(float deltaTime) {

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

    void MainMenuBar::draw() {

    }
}
