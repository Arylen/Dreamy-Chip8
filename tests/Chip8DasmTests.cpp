#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8Dasm.h"
#include <cstdint>
#include <format>

#define DASM dc8::core::emulation::disassembleInstruction
constexpr const char* TAG = "DASM";
#define NAME(name) std::format("[{}] {}", TAG, #name)

TEST_CASE(NAME("CLS"), TAG) {
    REQUIRE(DASM(0x00E0) == "CLS");
}

TEST_CASE(NAME("RET"), TAG) {
    REQUIRE(DASM(0x00EE) == "RET");
}

TEST_CASE(NAME("SYS  NNN"), TAG) {
    for (uint16_t sysCall = 0; sysCall <= 0xFFF; sysCall++) {
        if (sysCall == 0x00EE || sysCall == 0x00E0)
            continue;

        // Don't need to do some bitmasking here since 0NNN op for SYS instr.
        CAPTURE(sysCall);
        REQUIRE(DASM(sysCall) == std::format("SYS  {:04X}", sysCall));
    }
}

TEST_CASE(NAME("JP   NNN"), TAG) {
    for (uint16_t addr = 0; addr <= 0xFFF; addr++) {
        uint16_t instruction = 0x1000 | addr;
        CAPTURE(instruction, addr);
        REQUIRE(DASM(instruction) == std::format("JP   {:04X}", addr));
    }
}

TEST_CASE(NAME("CALL NNN"), TAG) {
    for (uint16_t addr = 0; addr <= 0xFFF; addr++) {
        uint16_t instruction = 0x2000 | addr;
        CAPTURE(instruction, addr);
        REQUIRE(DASM(instruction) == std::format("CALL {:04X}", addr));
    }
}

TEST_CASE(NAME("SE   VX, NN"), TAG) {
    for (uint8_t reg = 0; reg <= 0x0F; reg++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0x3000 | (reg << 8) | nn;
            CAPTURE(instruction, reg, nn);
            REQUIRE(DASM(instruction) == std::format("SE   V{:X}, {:02X}", reg, nn));
        }
    }
}

TEST_CASE(NAME("SNE  VX, NN"), TAG) {
    for (uint8_t reg = 0; reg <= 0x0F; reg++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0x4000 | (reg << 8) | nn;
            CAPTURE(instruction, reg, nn);
            REQUIRE(DASM(instruction) == std::format("SNE  V{:X}, {:02X}", reg, nn));
        }
    }
}

TEST_CASE(NAME("SE   VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x5000 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SE   V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("LD   VX, NN"), TAG) {
    for (uint8_t reg = 0; reg <= 0x0F; reg++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0x6000 | (reg << 8) | nn;
            CAPTURE(instruction, reg, nn);
            REQUIRE(DASM(instruction) == std::format("LD   V{:X}, {:02X}", reg, nn));
        }
    }
}

TEST_CASE(NAME("ADD  VX, NN"), TAG) {
    for (uint8_t reg = 0; reg <= 0x0F; reg++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0x7000 | (reg << 8) | nn;
            CAPTURE(instruction, reg, nn);
            REQUIRE(DASM(instruction) == std::format("ADD  V{:X}, {:02X}", reg, nn));
        }
    }
}

TEST_CASE(NAME("LD   VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8000 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("LD   V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("OR   VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8001 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("OR   V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("AND  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8002 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("AND  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("XOR  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8003 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("XOR  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("ADD  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8004 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("ADD  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("SUB  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8005 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SUB  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("SHR  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8006 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SHR  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("SUBN VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x8007 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SUBN V{:X}, V{:X}", r1, r2));
        }
    }
}

// String of illegal ops here.
TEST_CASE(NAME("UNK  8X YN"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            for (uint8_t n = 0; n <= 0x0F; n++) {
                if (n <= 0x7 || n == 0xE)
                    continue;
                uint16_t instruction = 0x8000 | (r1 << 8) | (r2 << 4) | n;
                CAPTURE(instruction, r1, r2, n);
                REQUIRE(DASM(instruction) == std::format("UNK  {:02X} {:02X}", (instruction & 0xFF00) >> 8 , (instruction & 0xFF)));
            }
        }
    }
}

TEST_CASE(NAME("SHL  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x800E | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SHL  V{:X}, V{:X}", r1, r2));
        }
    }
}
