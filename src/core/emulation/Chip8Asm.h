#pragma once

#include "core/emulation/Chip8Op.h"
#include <string>
#include <vector>

namespace dc8::core::emulation {
    namespace detail {
        std::vector<std::string> getParts(std::string instruction);
    }
    dc8::core::emulation::Chip8Op assembleInstruction(std::string input);
    std::vector<dc8::core::emulation::Chip8Op> assembleProgram(std::vector<std::string> program);
}
