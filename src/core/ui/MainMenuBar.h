#pragma once

#include "core/AppState.h"
#include "core/ui/UiElement.h"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_error.h>

namespace dc8::core::ui {
    class MainMenuBar : public UiElement {
    public:
        MainMenuBar(AppState& state);
        void drawUi() override;
    private:
        static void SDLCALL onFileSelected(void*, const char* const* files, int);
    };
}
