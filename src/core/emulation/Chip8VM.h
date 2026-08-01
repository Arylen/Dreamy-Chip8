#pragma once

#include <array>
#include <cstdint>

namespace dc8::core::emulation {
    class Chip8VM {
    public:
        Chip8VM();
        ~Chip8VM();
        void reset();
        void loadRomBytes(uint8_t data[], uint32_t len);
        void cycle();
        void writeMem(uint16_t address, uint8_t value);
        uint8_t readMem(uint16_t address) const;
    private:
        void loadFont();
        std::array<uint8_t, 4096> mem_;
        std::array<uint8_t, 16> v_;
        std::array<uint8_t,  64 * 32> vram_;
        uint16_t i_;
        uint16_t pc_;
    };
}
