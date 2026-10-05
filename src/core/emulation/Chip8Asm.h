#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dc8::core::emulation {
    namespace detail {
        std::vector<std::string> getParts(std::string instruction);
    }
    class Chip8Asm {
    public:
            uint16_t assembleInstruction(std::string input);
            std::vector<uint16_t> assembleProgram(std::vector<std::string> program);
    };
}
