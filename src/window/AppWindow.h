#pragma once

#include "core/Entity.h"
#include <SDL3/SDL_video.h>
#include <memory>

namespace dc8::platform {
    class AppWindow {
    public:
        AppWindow() = default;
        ~AppWindow();

        AppWindow(const AppWindow&) = delete;
        AppWindow& operator=(const AppWindow&) = delete;

        bool create();
        void run();
        void setRootEntity(std::unique_ptr<core::Entity> entity);
    private:
        SDL_Window* window_{nullptr};
        SDL_GLContext glContext_{nullptr};
        std::unique_ptr<core::Entity> rootEntity_;

        bool render();
    };
}
