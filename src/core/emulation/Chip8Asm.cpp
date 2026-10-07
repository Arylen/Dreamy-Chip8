#include "Chip8Asm.h"
#include <cstdint>
#include <regex>
#include <vector>

namespace dc8::core::emulation {
    namespace detail {
        static const std::regex partRegex(R"(\w+)");
        std::vector<std::string> getParts(std::string instruction) {
            std::vector<std::string> parts;

            instruction = instruction.substr(0, instruction.find(';'));

            auto iterator = std::sregex_iterator(instruction.begin(), instruction.end(), partRegex);
            for (; iterator != std::sregex_iterator(); ++iterator) {
                parts.push_back(iterator->str());
            }

            return parts;
        }
    }

    uint16_t Chip8Asm::assembleInstruction(std::string input) {
        return 0x0000;
    }

    std::vector<uint16_t> Chip8Asm::assembleProgram(std::vector<std::string> program) {
        return std::vector<uint16_t>();
    }
}
