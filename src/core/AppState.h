#pragma once


#include "core/emulation/Chip8VM.h"

namespace dc8::core {
    struct AppState {
        // Emulator
        emulation::Chip8VM vm;

        // VM State
        bool vmIsPaused = true;

        // App Behavior

        // Window States
        bool showLog = true;
        bool showCpuState = true;
        bool showQuickControls = true;
    };
}
