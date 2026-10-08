#include "Chip8Asm.h"
#include "core/emulation/Chip8Op.h"
#include <cctype>
#include <cstdint>
#include <exception>
#include <functional>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <optional>


namespace {
    using Chip8Op = dc8::core::emulation::Chip8Op;
    using AsmEncoder = std::function<std::optional<Chip8Op>(const std::vector<std::string>& parts)>;

    // TODO: Consider passing reference here. Allocations probably aren't a big concern since this is not a hot path.
    std::string toUpper(std::string text) {
        for (char& c : text) {
            c = (char)std::toupper((unsigned char) c);
        }
        return text;
    }

    uint16_t parseHex(std::string value, uint16_t maximum = 0x0FFF) {
        size_t parsedCharCount = 0;
        unsigned long address = 0;

        try {
            address = std::stoul(value, &parsedCharCount, 16);
        } catch (const std::exception&) {
            throw std::invalid_argument("Value could not be parsed as hex.");
        }

        if (parsedCharCount != value.length()) {
            throw std::invalid_argument("Value did not match expected length comparing chars to bytes.");
        }

        if (address > maximum) {
            throw std::invalid_argument("Value parsed exceeded maximum");
        }

        return (uint16_t)(address & 0x0FFF);
    }

    // JP NNN  -  1NNN
    Chip8Op asmJp(std::vector<std::string> parts) {
        if (parts.size() != 2) {
            throw std::invalid_argument("Invalid amount of arguments for JP assembly.");
        }

        uint16_t jpAddr = parseHex(parts[1], 0x0FFF);

        Chip8Op op;
        op.setFamily(0x1);
        op.setNNN(jpAddr);
        return op;
    }

    static const std::unordered_map<std::string, AsmEncoder> encoderLut_ = {
        {"CLS", [](const std::vector<std::string>&) -> Chip8Op { return Chip8Op(0x00E0); } },
        {"RET", [](const std::vector<std::string>&) -> Chip8Op { return Chip8Op(0x00EE); } },
        {"JP", asmJp },
    };
}

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

        AsmEncoder getEncoder(std::string family) {
            auto uppercaseFamily = toUpper(family);
            auto hasEncoder = encoderLut_.contains(uppercaseFamily);
            if (hasEncoder) {
                return encoderLut_.at(uppercaseFamily);
            }
            throw std::invalid_argument("Invalid instruction.");
        }
    }

    // Note: Empty instruction is a valid result in some cases.
    std::optional<Chip8Op> assembleInstruction(std::string instruction) {
        auto parts = detail::getParts(instruction);
        if (parts.empty()) {
            return std::nullopt;
        }

        try {
            AsmEncoder encoder = detail::getEncoder(parts[0]);
            return encoder(parts);
        } catch (std::exception& exception) {
            // Valid error here.
            throw;
        }
    }

    std::vector<Chip8Op> assembleProgram(std::vector<std::string> program) {
        return std::vector<Chip8Op>();
    }
}
