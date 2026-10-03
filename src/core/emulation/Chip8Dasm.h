#pragma once

#include "core/emulation/Chip8Op.h"
#include <string>

namespace dc8::core::emulation {
    std::string disassembleInstruction(const Chip8Op& op);
}
