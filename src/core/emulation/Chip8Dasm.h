#pragma once

#include "core/emulation/Chip8Op.h"
#include <format>
#include <string>

namespace dc8::core::emulation {
    inline std::string disassembleInstruction(uint16_t instruction) {
        Chip8Op op { .raw = instruction };

        switch (op.getFamily()) {
            case 0x0:
                if (op.raw == 0x00E0) return std::format("CLS");
                if (op.raw == 0x00EE) return std::format("RET");
                return std::format("SYS  {:04X}", op.getNNN());
            case 0x1: return std::format("JP   {:04X}", op.getNNN());
            case 0x2: return std::format("CALL {:04X}", op.getNNN());
            case 0x3: return std::format("SE   V{:X}, {:02X}", op.getX(), op.getNN());
            case 0x4: return std::format("SNE  V{:X}, {:02X}", op.getX(), op.getNN());
            case 0x5:
                if (op.getN() == 0x0) return std::format("SE   V{:X}, V{:X}",  op.getX(), op.getY());
                break;
            case 0x6: return std::format("LD   V{:X}, {:02X}", op.getX(), op.getNN());
            case 0x7: return std::format("ADD  V{:X}, {:02X}", op.getX(), op.getNN());
            case 0x8:
                if (op.getN() == 0x0) return std::format("LD   V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x1) return std::format("OR   V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x2) return std::format("AND  V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x3) return std::format("XOR  V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x4) return std::format("ADD  V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x5) return std::format("SUB  V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x6) return std::format("SHR  V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0x7) return std::format("SUBN V{:X}, V{:X}", op.getX(), op.getY());
                if (op.getN() == 0xE) return std::format("SHL  V{:X}, V{:X}", op.getX(), op.getY());
                break;
            case 0x9:
                if (op.getN() == 0x0) return std::format("SNE  V{:X}, V{:X}", op.getX(), op.getY());
                break;
            case 0xA: return std::format("LD   I,  {:03X}", op.getNNN());
            case 0xB: return std::format("JP   V0, {:03X}", op.getNNN());
            case 0xC: return std::format("RND  V{:X}, {:02X}", op.getX(), op.getNN());
            case 0xD: return std::format("DRW  V{:X}, V{:X}, {:X}", op.getX(), op.getY(), op.getN());
            case 0xE:
                if (op.getNN() == 0x9E) return std::format("SKP  V{:X}", op.getX());
                if (op.getNN() == 0xA1) return std::format("SKNP V{:X}", op.getX());
                break;
            case 0xF:
                if (op.getNN() == 0x07) return std::format("LD   V{:X}, DT", op.getX());
                if (op.getNN() == 0x0A) return std::format("LD   V{:X}, K",  op.getX());
                if (op.getNN() == 0x15) return std::format("LD   DT, V{:X}", op.getX());
                if (op.getNN() == 0x18) return std::format("LD   ST, V{:X}", op.getX());
                if (op.getNN() == 0x1E) return std::format("ADD  I,  V{:X}", op.getX());
                if (op.getNN() == 0x29) return std::format("LD   F,  V{:X}", op.getX());
                if (op.getNN() == 0x33) return std::format("LD   B,  V{:X}", op.getX());
                if (op.getNN() == 0x55) return std::format("LD   @I, V{:X}", op.getX());
                if (op.getNN() == 0x55) return std::format("LD   V{:X}, @I", op.getX());
                break;
        }

        return std::format("UNK  {:02X} {:02X}", op.getHi(), op.getLo());
    }

    inline std::string disassembleInstruction(uint8_t hi, uint8_t lo) {
        return disassembleInstruction((hi << 8) | lo);
    }
}
