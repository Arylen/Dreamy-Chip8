#include "LogWindow.h"

#include "core/Log.h"

#include "imgui.h"

namespace dc8::core::ui::windows {
    LogWindow::LogWindow(AppState& state) : UiElement(state) { }
    void LogWindow::drawUi() {
        if (!state_.showLog) {
            return;
        }

        if (ImGui::Begin("Logs")) {
            bool isAtBottom = ImGui::GetScrollY() >= ImGui::GetScrollMaxY();

            auto logs = log::getMessages();
            for (const auto& logMsg : logs) {
                ImGui::TextUnformatted(logMsg.c_str());
            }

            if (isAtBottom) {
                ImGui::SetScrollHereY(1.0f);
            }
        }
        ImGui::End();
    }
}
