#include "Chip8VM.h"
#include "core/emulation/Chip8Consts.h"
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
        loadFont();
    }

    void Chip8VM::loadRomBytes(uint8_t data[], uint32_t len) {

    }

    void Chip8VM::cycle() {

    }

    void Chip8VM::loadFont() {
        for (int i = 0; i < FontData.size(); i++) {
            writeMem(FontStartAddress + i, FontData.at(i));
        }
    }

    void Chip8VM::writeMem(uint16_t address, uint8_t value) {
        mem_[address] = value;
    }

    uint8_t Chip8VM::readMem(uint16_t address) const {
        return mem_.at(address);
    }
}
