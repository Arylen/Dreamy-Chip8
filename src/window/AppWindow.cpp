#include "window/AppWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "core/Log.h"

namespace dc8::platform {
    AppWindow::~AppWindow() {
        if (window_) {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
        SDL_Quit();
    }

    bool AppWindow::create() {
        log::info("Initializing SDL3.");
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            log::critical("SDL3 initialization failed: {}", SDL_GetError());
            return false;
        }

        log::info("Creating SDL3 Window.");
        window_ = SDL_CreateWindow(
            "Dreamy CHIP-8",
            800, 600,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
        );
        if (!window_) {
            log::error("SDL3 Window creation failed: {}", SDL_GetError());
            return false;
        }

        renderer_ = SDL_CreateRenderer(window_, nullptr);
        if (!renderer_) {
            log::error("SDL Renderer creation failed: {}", SDL_GetError());
            return false;
        }

        displayTex_ = SDL_CreateTexture(
            renderer_,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            64,
            32
        );
        if (!displayTex_) {
            log::error("Display Texture creation failed: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    void AppWindow::run() {
        bool running = true;
        while (running) {
            SDL_Event event{};

            if (!SDL_WaitEvent(&event)) {
                log::error("SDL event wait failed: {}", SDL_GetError());
                break;
            }

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
            }
        }
    }
}
