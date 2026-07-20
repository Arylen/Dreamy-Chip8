#include "LogWindow.h"
#include "imgui.h"

namespace dc8::core::ui::windows {
    LogWindow::LogWindow(AppState& state) : UiElement(state) { }
    void LogWindow::drawUi() {
        if (!state_.showLog) {
            return;
        }

        if (ImGui::Begin("Logs")) {
            ImGui::TextUnformatted("Logs Placeholder");
        }
        ImGui::End();
    }
}
