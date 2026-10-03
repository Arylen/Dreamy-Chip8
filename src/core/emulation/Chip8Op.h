#pragma once

#include <cstdint>

namespace dc8::core::emulation {
    /*
     * 1234
     * ---N
     * --NN
     * -NNN
     * -X--
     * --Y-
     */
    struct Chip8Op {
        explicit Chip8Op(uint16_t raw) : raw_(raw) { }

        uint8_t getFamily() const {
            return (raw_ & 0xF000) >> 12;
        }

        uint8_t getN() const {
            return (raw_ & 0x000F);
        }

        uint8_t getNN() const {
            return (raw_ & 0x00FF);
        }

        uint16_t getNNN() const {
            return (raw_ & 0x0FFF);
        }

        uint8_t getX() const {
            return (raw_ & 0x0F00) >> 8;
        }

        uint8_t getY() const {
            return (raw_ & 0x00F0) >> 4;
        }

        uint8_t getHi() const {
            return (raw_ & 0xFF00) >> 8;
        }

        uint8_t getLo() const {
            return getNN();
        }

        uint16_t getRaw() const {
            return raw_;
        }
    private:
        uint16_t raw_;
    };
}
