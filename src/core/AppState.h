#pragma once

#include "core/emulation/Chip8VM.h"
namespace dc8::core {
    struct AppState {
        // Emulator
        emulation::Chip8VM vm;

        // Window States
        bool showLog;
    };
}
