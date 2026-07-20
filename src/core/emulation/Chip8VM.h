#pragma once

#include <cstdint>

namespace dc8::core::emulation {
    class Chip8VM {
    public:
        Chip8VM();
        ~Chip8VM();
        void reset();
        void loadRomBytes(uint8_t data[], uint32_t len);
        void cycle();
    };
}
