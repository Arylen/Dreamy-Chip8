#pragma once
#include "Log.h"
#include "core/emulation/Chip8VM.h"
#include "spdlog/common.h"
namespace dc8::core {
    struct AppState {
        // Emulator
        emulation::Chip8VM vm;

        // VM State
        bool vmIsPaused = true;

        // App Behavior
        spdlog::level::level_enum logLevel;

        // Window States
        bool showLog = true;
        bool showCpuState = true;
        bool showQuickControls = true;
    };
}
