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

    bool isHexChar(char c) {
        return (c >= '0' && c <= '9')
            || (c >= 'A' && c <= 'F')
            || (c >= 'a' && c <= 'f');
    }

    bool isHexString(std::string s) {
        for (size_t i = 0; i < s.length(); i++) {
            if (!isHexChar(s[i])) {
                return false;
            }
        }
        return true;
    }

    bool isRegister(std::string text) {
        if (text.length() != 2) {
            return false;
        }
        if (text[0] != 'V' && text[0] != 'v') {
            return false;
        }
        if (!isHexChar(text[1])) {
            return false;
        }
        return true;
    }

    uint8_t parseHexNibble(char v) {
        if (!isHexChar(v)) {
            throw std::invalid_argument("Hex byte attempted to be parsed was not even hex.");
        }
        if (v >= 'a' && v <= 'f') {
            return (v - 'a') + 10;
        }
        if (v >= 'A' && v <= 'F') {
            return (v - 'A') + 10;
        }
        if (v >= '0' && v <= '9') {
            return v - '0';
        }
        throw std::invalid_argument("Impossible situation. Single-char hex got through and not returned above.");
    }

    uint8_t parseRegister(std::string value) {
        if (!isRegister(value)) {
            throw std::invalid_argument("Attempt to parse register that failed to parse.");
        }
        return parseHexNibble(value[1]);
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

    // 1NNN  -  JP NNN
    // BNNN  -  JP V0, NNN
    Chip8Op asmJp(std::vector<std::string> parts) {
        if (parts.size() == 2) {
            uint16_t jpAddr = parseHex(parts[1], 0x0FFF);
            Chip8Op op;
            op.setFamily(0x1);
            op.setNNN(jpAddr);
            return op;
        }
        if (parts.size() == 3) {
            uint16_t jpAddr = parseHex(parts[2], 0x0FFF);

            if (!isRegister(parts[1])) {
                throw std::invalid_argument("Expected register as the first operand");
            }
            if (parseRegister(parts[1]) != 0) {
                throw std::invalid_argument("Expected V0 register.");
            }

            Chip8Op op;
            op.setFamily(0xB);
            op.setNNN(jpAddr);

            return op;
        }
        throw std::invalid_argument("Invalid amount of operands.");
    }

    // 0NNN  -  SYS NNN
    Chip8Op asmSys(std::vector<std::string> parts) {
        if (parts.size() != 2) {
            throw std::invalid_argument("Invalid amount of operands.");
        }

        uint16_t call = parseHex(parts[1], 0x0FFF);

        if (call == 0x0E0) {
            throw std::invalid_argument("Attempted reserved SYS call for 0E0, Reserved for CLS");
        }

        if (call == 0x0EE) {
            throw std::invalid_argument("Attempted reserved SYS call for 0E0, Reserved for RET");
        }

        Chip8Op op;
        op.setFamily(0x0);
        op.setNNN(call);

        return op;
    }

    // 2NNN  -  CALL NNN
    Chip8Op asmCall(std::vector<std::string> parts) {
        if (parts.size() != 2) {
            throw std::invalid_argument("Invalid amount of operands.");
        }

        uint16_t addr = parseHex(parts[1], 0x0FFF);

        Chip8Op op;
        op.setFamily(0x2);
        op.setNNN(addr);

        return op;
    }

    // 8XY1  -  OR VX, VY
    Chip8Op asmOr(std::vector<std::string> parts) {
        if (parts.size() != 3) {
            throw std::invalid_argument("Invalid amount of operands.");
        }
        if (!isRegister(parts[1])) {
            throw std::invalid_argument("First operand is not a register.");
        }
        if (!isRegister(parts[2])) {
            throw std::invalid_argument("Second operand is not a register.");
        }

        Chip8Op op;

        op.setFamily(0x8);
        op.setX(parseRegister(parts[1]));
        op.setY(parseRegister(parts[2]));
        op.setN(0x1);

        return op;
    }

    // 3XNN  -  SE VX, NN
    // 5XY0  -  SE VX, VY
    Chip8Op asmSe(std::vector<std::string> parts) {
        if (parts.size() != 3) {
            throw std::invalid_argument("Invalid amount of arguments for JP assembly.");
        }
        if (!isRegister(parts[1])) {
            throw std::invalid_argument("First operand was not a register.");
        }
        if (!isRegister(parts[2]) && !isHexString(parts[2])) {
            throw std::invalid_argument("Second operand was not a register or a hex string.");
        }

        bool hasImmediate = !isRegister(parts[2]);

        Chip8Op op;

        op.setFamily(hasImmediate ? 0x3 : 0x5);
        op.setX(parseRegister(parts[1]));
        if (hasImmediate) {
            op.setNN(parseHex(parts[2]));
        } else {
            op.setY(parseRegister(parts[2]));
            op.setN(0);
        }

        return op;
    }

    static const std::unordered_map<std::string, AsmEncoder> encoderLut_ = {
        {"CLS", [](const std::vector<std::string>&) -> Chip8Op { return Chip8Op(0x00E0); } },
        {"RET", [](const std::vector<std::string>&) -> Chip8Op { return Chip8Op(0x00EE); } },
        {"SYS", asmSys },
        {"JP", asmJp },
        {"CALL", asmCall },
        {"SE", asmSe },
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
