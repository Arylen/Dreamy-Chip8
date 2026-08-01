#pragma once

namespace dc8::core::emulation {
    enum Chip8Exception {
        NONE,
        ROM_TOO_LARGE,
        INVALID_OP,
        INVALID_OP_FAMILY,
    };
}
