#include "window/AppWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_opengl.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include "core/Log.h"
#include <utility>

namespace dc8::platform {
    AppWindow::~AppWindow() {
        if (glContext_) {
            SDL_GL_DestroyContext(glContext_);
            glContext_ = nullptr;
        }
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

        log::info("Setting OpenGL attributes.");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        log::info("Creating SDL3 Window.");
        window_ = SDL_CreateWindow(
            "Dreamy CHIP-8",
            800, 600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
        );
        if (!window_) {
            log::error("SDL3 Window creation failed: {}", SDL_GetError());
            return false;
        }

        log::info("Creating OpenGL context");
        glContext_ = SDL_GL_CreateContext(window_);
        if (!glContext_) {
            log::error("OpenGL Context creation failed: {}", SDL_GetError());
            return false;
        }

        if (!SDL_GL_SetSwapInterval(1)) {
            log::warn("Could not enable VSync: {}", SDL_GetError());
        }

        log::info("OpenGL version: {}", (const char*)glGetString(GL_VERSION));
        log::info("OpenGL renderer: {}", (const char*)glGetString(GL_RENDERER));

        return true;
    }

    void AppWindow::run() {
        bool running = true;
        while (running) {
            SDL_Event event{};

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                }
                if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                    running = false;
                }
            }

            if (rootEntity_) {
                rootEntity_->update(0);
            }

            if (running && !render()) {
                running = false;
            }
        }
    }

    bool AppWindow::render() {
        int pixWidth = 0;
        int pixHeight = 0;

        if (!SDL_GetWindowSizeInPixels(window_, &pixWidth, &pixHeight)) {
            log::error("Could not get window pixel size: {}", SDL_GetError());
            return false;
        }

        glViewport(0, 0, pixWidth, pixHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!SDL_GL_SwapWindow(window_)) {
            log::error("OpenGL buffer swap failed: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    void AppWindow::setRootEntity(std::unique_ptr<core::Entity> entity) {
        rootEntity_ = std::move(entity);
    }
}
