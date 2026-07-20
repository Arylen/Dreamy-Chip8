#pragma once

#include "Application.h"
#include <SDL3/SDL_video.h>

namespace dc8::platform {
    class AppWindow {
    public:
        AppWindow(Application& app);
        ~AppWindow();

        AppWindow(const AppWindow&) = delete;
        AppWindow& operator=(const AppWindow&) = delete;

        bool create();
        void run();
    private:
        SDL_Window* window_{nullptr};
        SDL_GLContext glContext_{nullptr};
        Application& app_;

        bool render();
    };
}
