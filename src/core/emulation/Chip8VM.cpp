#include "Chip8VM.h"
#include "core/Log.h"
#include "core/emulation/Chip8Consts.h"
#include "core/emulation/Chip8Exception.h"
#include "core/emulation/Chip8Op.h"
#include <csignal>
#include <cstddef>
#include <cstdint>

namespace dc8::core::emulation {
    Chip8VM::Chip8VM() {
        reset();
    }

    Chip8VM::~Chip8VM() {

    }

    void Chip8VM::reset() {
        mem_.fill(0);
        vram_.fill(0);
        v_.fill(0);
        i_ = 0;
        pc_ = RomStartAddress;
        loadFont();
    }

    void Chip8VM::loadRomBytes(uint8_t data[], uint32_t len) {
        if (len >= mem_.size() - RomStartAddress) {
            return raiseException(Chip8Exception::ROM_TOO_LARGE);
        }
        for (size_t i = 0; i < len; i++) {
            writeMem(RomStartAddress + i, data[i]);
        }
    }

    void Chip8VM::cycle() {
        Chip8Op instruction {
            .raw = readMem16(pc_)
        };
        pc_ += 2;

        execute(instruction);
    }

    void Chip8VM::execute(Chip8Op op) {
        switch (op.getFamily()) {
            case 0x0:
                switch (op.getNN()) {
                    case 0x00E0: // CLS
                        vram_.fill(0);
                        break;
                    default:
                        return raiseException(Chip8Exception::INVALID_OP_FAMILY);
                }
                break;
            case 0x1: // JMP NNN
                pc_ = op.getNNN();
                break;
            case 0x6: // SET VX, NN
                v_[op.getX()] = op.getNN();
                break;
            case 0x7: // ADD VX, NN
                v_[op.getX()] += op.getNN();
                break;
            case 0xA: // SET I, NNN
                i_ = op.getNNN();
                break;
            case 0xD: // DRW X, Y, N
                drawSprite(v_.at(op.getX()), v_.at(op.getY()), op.getN());
                break;
            default:
                return raiseException(Chip8Exception::INVALID_OP_FAMILY);
        }
    }

    void Chip8VM::drawSprite(uint8_t x, uint8_t y, uint8_t n) {
        log::info("DRAW x={}, y={}, n={}", x, y, n);
    }

    void Chip8VM::raiseException(Chip8Exception exception) {
        currentException_ = exception;
    }

    void Chip8VM::loadFont() {
        for (size_t i = 0; i < FontData.size(); i++) {
            writeMem(FontStartAddress + i, FontData.at(i));
        }
    }

    void Chip8VM::writeMem(uint16_t address, uint8_t value) {
        mem_[address] = value;
    }

    uint8_t Chip8VM::readMem(uint16_t address) const {
        return mem_.at(address);
    }

    uint16_t Chip8VM::readMem16(uint16_t address) const {
        return readMem(address) | (readMem(address + 1) << 8);
    }
}
