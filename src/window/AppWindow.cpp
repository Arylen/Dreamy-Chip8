#include "window/AppWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include "core/Log.h"

namespace dc8::platform {
    AppWindow::~AppWindow() {
        if (gpuDevice_) {
            SDL_ReleaseWindowFromGPUDevice(gpuDevice_, window_);
            SDL_DestroyGPUDevice(gpuDevice_);
            gpuDevice_ = nullptr;
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

        log::info("Creating GPU device.");
        gpuDevice_ = SDL_CreateGPUDevice(
            SDL_GPU_SHADERFORMAT_SPIRV |
                SDL_GPU_SHADERFORMAT_DXBC |
                SDL_GPU_SHADERFORMAT_DXIL |
                SDL_GPU_SHADERFORMAT_METALLIB,
            true,
            nullptr
        );
        if (!gpuDevice_) {
            log::error("SDL3 GPU Device creation failed: {}", SDL_GetError());
            return false;
        }
        log::info("SDL GPU Driver: {}", SDL_GetGPUDeviceDriver(gpuDevice_));

        if (!SDL_ClaimWindowForGPUDevice(gpuDevice_, window_)) {
            log::error("SDL GPU could not claim window: {}", SDL_GetError());
            SDL_DestroyGPUDevice(gpuDevice_);
            gpuDevice_ = nullptr;
            return false;
        }

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

            if (running && !render()) {
                running = false;
            }
        }
    }

    bool AppWindow::render() {
        SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice_);
        if (!commandBuffer) {
            log::error("Failed to acquire GPU command buffer: {}", SDL_GetError());
            return false;
        }

        SDL_GPUTexture* swapchainTex = nullptr;
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(
            commandBuffer,
            window_,
            &swapchainTex,
            nullptr,
            nullptr
        )) {
            log::error("Failed to acquire swapchain tex: {}", SDL_GetError());
            SDL_CancelGPUCommandBuffer(commandBuffer);
            return false;
        }

        if (!swapchainTex) {
            SDL_CancelGPUCommandBuffer(commandBuffer);
            return true;
        }

        SDL_GPUColorTargetInfo colorTarget {};
        colorTarget.texture = swapchainTex;
        colorTarget.clear_color = SDL_FColor {0.0f, 0.0f, 0.0f, 1.0f};
        colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTarget.store_op = SDL_GPU_STOREOP_STORE;

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(
            commandBuffer,
            &colorTarget,
            1,
            nullptr
        );
        SDL_EndGPURenderPass(renderPass);

        if (!SDL_SubmitGPUCommandBuffer(commandBuffer)) {
            log::error("Failed to submit GPU command buffer: {}", SDL_GetError());
            return false;
        }

        return true;
    }
}
