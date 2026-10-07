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
        explicit Chip8Op(uint16_t raw = 0) : raw_(raw) { }

        uint8_t getFamily() const {
            return (raw_ & 0xF000) >> 12;
        }

        void setFamily(uint8_t value) {
            raw_ = (raw_ & 0x0FFF) | ((value & 0xF) << 12);
        }

        uint8_t getN() const {
            return (raw_ & 0x000F);
        }

        void setN(uint8_t value) {
            raw_ = (raw_ & 0xFFF0) | (value & 0x0F);
        }

        uint8_t getNN() const {
            return (raw_ & 0x00FF);
        }

        void setNN(uint8_t value) {
            raw_ = (raw_ & 0xFF00) | value;
        }

        uint16_t getNNN() const {
            return (raw_ & 0x0FFF);
        }

        void setNNN(uint16_t value) {
            raw_ = (raw_ & 0xF000) | (value & 0x0FFF);
        }

        uint8_t getX() const {
            return (raw_ & 0x0F00) >> 8;
        }

        void setX(uint8_t value) {
            raw_ = (raw_ & 0xF0FF) | ((value & 0xF) << 8);
        }

        uint8_t getY() const {
            return (raw_ & 0x00F0) >> 4;
        }

        void setY(uint8_t value) {
            raw_ = (raw_ & 0xFF0F) | ((value & 0xF) << 4);
        }

        uint8_t getHi() const {
            return (raw_ & 0xFF00) >> 8;
        }

        void setHi(uint8_t value) {
            raw_ = (raw_ & 0x00FF) | (value << 8);
        }

        uint8_t getLo() const {
            return getNN();
        }

        void setLo(uint8_t value) {
            setNN(value);
        }

        uint16_t getRaw() const {
            return raw_;
        }

    private:
        uint16_t raw_;
    };
}
