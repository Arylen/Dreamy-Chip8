#include "MainMenuBar.h"

#include "core/AppState.h"
#include "core/Log.h"
#include "core/ui/UiElement.h"

#include "imgui.h"
#include "spdlog/common.h"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_error.h>

namespace dc8::core::ui {
    MainMenuBar::MainMenuBar(AppState& state): UiElement(state) { }

    void MainMenuBar::drawUi() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open ROM")) {
                    // Lordy
                    constexpr SDL_DialogFileFilter romFilters[] = {
                        { "Chip-8 ROMs", "ch8;c8;sc8;xo8;bin" },
                        { "All Files", "*" }
                    };
                    SDL_ShowOpenFileDialog(
                        &MainMenuBar::onFileSelected,
                        nullptr,
                        nullptr,
                        romFilters,
                        SDL_arraysize(romFilters),
                        nullptr,
                        false
                    );
                }
                ImGui::EndMenu();
            }
            drawWindowMenu();
            drawSettingsMenu();
            ImGui::EndMainMenuBar();
        }
    }

    void SDLCALL MainMenuBar::onFileSelected(void*, const char* const* files, int) {
        if (!files) {
            dc8::log::error("File picker failed: {}", SDL_GetError());
            return;
        }

        if (!files[0]) {
            dc8::log::info("No files selected!");
            return;
        }

        dc8::log::info("Selected ROM: {}", files[0]);
    }

    void MainMenuBar::drawWindowMenu() {
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Logs", nullptr, &state_.showLog);
            ImGui::MenuItem("CPU State", nullptr, &state_.showCpuState);
            ImGui::MenuItem("Quick Controls", nullptr, &state_.showQuickControls);
            ImGui::EndMenu();
        }
    }

    void drawLogLevelMenuItem(const char* title, spdlog::level::level_enum level) {
        if (ImGui::MenuItem(title, nullptr, log::hasLogLevel(level))) {
            log::setLogLevel(level);
        }
    }

    void MainMenuBar::drawSettingsMenu() {
        if (ImGui::BeginMenu("Settings")) {
            if (ImGui::BeginMenu("Log Level")) {
                drawLogLevelMenuItem("Trace", spdlog::level::trace);
                drawLogLevelMenuItem("Debug", spdlog::level::debug);
                drawLogLevelMenuItem("Info", spdlog::level::info);
                drawLogLevelMenuItem("Warn", spdlog::level::warn);
                drawLogLevelMenuItem("Error", spdlog::level::err);
                drawLogLevelMenuItem("Critical", spdlog::level::critical);
                drawLogLevelMenuItem("Off", spdlog::level::off);
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
    }
}
