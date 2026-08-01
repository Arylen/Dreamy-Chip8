#pragma once

#include "core/emulation/Chip8Exception.h"
#include "core/emulation/Chip8Op.h"
#include <array>
#include <cstdint>

namespace dc8::core::emulation {
    class Chip8VM {
    public:
        Chip8VM();
        ~Chip8VM();

        // Management
        void reset();
        void loadRomBytes(uint8_t data[], uint32_t len);
        bool hasException();
        Chip8Exception getException();

        // CPU emu
        void cycle();
        void execute(Chip8Op op);

        // Memory
        void writeMem(uint16_t address, uint8_t value);
        uint8_t readMem(uint16_t address) const;
        uint16_t readMem16(uint16_t address) const;

        // Getters
        uint16_t getPc() const { return pc_; }
        uint16_t getI() const { return i_; }
        uint8_t getV(uint8_t idx) const { return v_.at(idx); }
        std::array<uint8_t, 4096> getMem() const { return mem_; }
        std::array<uint8_t,  64 * 32> getVram() const { return vram_; }
    private:
        void loadFont();
        void drawSprite(uint8_t x, uint8_t y, uint8_t n);
        void raiseException(Chip8Exception exception);

        Chip8Exception currentException_;

        std::array<uint8_t, 4096> mem_;
        std::array<uint8_t, 16> v_;
        std::array<uint8_t,  64 * 32> vram_;
        uint16_t i_;
        uint16_t pc_;
    };
}
