#include "MainMenuBar.h"

#include "core/AppState.h"
#include "core/Log.h"
#include "core/ui/UiElement.h"

#include "imgui.h"
#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_error.h>

namespace dc8::core::ui {
    MainMenuBar::MainMenuBar(AppState& state): UiElement(state) { }

    void MainMenuBar::drawUi() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open ROM")) {
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
            if (ImGui::BeginMenu("Windows")) {
                ImGui::MenuItem("Logs", nullptr, &state_.showLog);
                ImGui::EndMenu();
            }
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
}
