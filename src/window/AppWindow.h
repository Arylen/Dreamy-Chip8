#pragma once

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_video.h>

namespace dc8::platform {
    class AppWindow {
    public:
        AppWindow() = default;
        ~AppWindow();

        AppWindow(const AppWindow&) = delete;
        AppWindow& operator=(const AppWindow&) = delete;

        bool create();
        void run();
    private:
        SDL_Window* window_{nullptr};
        SDL_GPUDevice* gpuDevice_{nullptr};

        bool render();
    };
}
