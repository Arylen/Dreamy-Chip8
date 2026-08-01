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
        uint16_t raw;

        uint8_t getFamily() const {
            return (raw & 0xF000) >> 12;
        }

        uint8_t getN() const {
            return (raw & 0x000F);
        }

        uint8_t getNN() const {
            return (raw & 0x00FF);
        }

        uint16_t getNNN() const {
            return (raw & 0x0FFF);
        }

        uint8_t getX() const {
            return (raw & 0x0F00) >> 8;
        }

        uint8_t getY() const {
            return (raw & 0x00F0) >> 4;
        }
    };
}
