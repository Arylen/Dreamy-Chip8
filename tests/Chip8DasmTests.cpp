#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8Dasm.h"
#include "core/emulation/Chip8Op.h"
#include <cstdint>
#include <format>
#include <algorithm>

#define DASM(raw) dc8::core::emulation::disassembleInstruction(dc8::core::emulation::Chip8Op(raw))
constexpr const char* TAG = "[DASM]";
#define NAME(name) std::format("{} {}", TAG, #name)

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

TEST_CASE(NAME("UNK  5X YN"), TAG) {
    for (uint16_t nnn = 0; nnn <= 0xFFF; nnn++) {
        if ((nnn & 0xF) == 0x0)
            continue;
        uint16_t instruction = 0x5000 | nnn;
        CAPTURE(instruction, nnn);
        REQUIRE(DASM(instruction) == std::format("UNK  {:02X} {:02X}", (instruction & 0xFF00) >> 8 , (instruction & 0xFF)));
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

TEST_CASE(NAME("SNE  VX, VY"), TAG) {
    for (uint8_t r1 = 0; r1 <= 0x0F; r1++) {
        for (uint8_t r2 = 0; r2 <= 0x0F; r2++) {
            uint16_t instruction = 0x9000 | (r1 << 8) | (r2 << 4);
            CAPTURE(instruction, r1, r2);
            REQUIRE(DASM(instruction) == std::format("SNE  V{:X}, V{:X}", r1, r2));
        }
    }
}

TEST_CASE(NAME("UNK  9X YN"), TAG) {
    for (uint16_t nnn = 0; nnn <= 0xFFF; nnn++) {
        if ((nnn & 0xF) == 0x00)
            continue;
        uint16_t instruction = 0x9000 | nnn;
        CAPTURE(instruction, nnn);
        REQUIRE(DASM(instruction) == std::format("UNK  {:02X} {:02X}", (instruction & 0xFF00) >> 8 , (instruction & 0xFF)));
    }
}

TEST_CASE(NAME("LD   I,  NNN"), TAG) {
    for (uint16_t nnn = 0; nnn <= 0xFFF; nnn++) {
        uint16_t instruction = 0xA000 | nnn;
        CAPTURE(instruction, nnn);
        REQUIRE(DASM(instruction) == std::format("LD   I,  {:03X}", nnn));
    }
}

TEST_CASE(NAME("JP   V0, NNN"), TAG) {
    for (uint16_t nnn = 0; nnn <= 0xFFF; nnn++) {
        uint16_t instruction = 0xB000 | nnn;
        CAPTURE(instruction, nnn);
        REQUIRE(DASM(instruction) == std::format("JP   V0, {:03X}", nnn));
    }
}

TEST_CASE(NAME("RND  VX, NN"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0xC000 | (x << 8) | nn;
            CAPTURE(instruction, x, nn);
            REQUIRE(DASM(instruction) == std::format("RND  V{:X}, {:02X}", x, nn));
        }
    }
}

TEST_CASE(NAME("DRW  VX, VY, N"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        for (uint8_t y = 0; y <= 0x0F; y++) {
            for (uint8_t n = 0; n <= 0x0F; n++) {
                uint16_t instruction = 0xD000 | (x << 8) | (y << 4) | n;
                CAPTURE(instruction, x, n);
                REQUIRE(DASM(instruction) == std::format("DRW  V{:X}, V{:X}, {:X}", x, y, n));
            }
        }
    }
}

TEST_CASE(NAME("SKP  VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xE09E | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("SKP  V{:X}", x));
    }
}

TEST_CASE(NAME("SKNP VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xE0A1 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("SKNP V{:X}", x));
    }
}

TEST_CASE(NAME("UNK  EX NN"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            if (nn == 0x9E || nn == 0xA1)
                continue;
            uint16_t instruction = 0xE000 | (x << 8) | nn;
            CAPTURE(instruction, x, nn);
            REQUIRE(DASM(instruction) == std::format("UNK  {:02X} {:02X}", (instruction & 0xFF00) >> 8 , (instruction & 0xFF)));
        }
    }
}

TEST_CASE(NAME("LD   VX, DT"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF007 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   V{:X}, DT", x));
    }
}

TEST_CASE(NAME("LD   VX, K"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF00A | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   V{:X}, K", x));
    }
}

TEST_CASE(NAME("LD   DT, VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF015 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   DT, V{:X}", x));
    }
}

TEST_CASE(NAME("LD   ST, VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF018 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   ST, V{:X}", x));
    }
}

TEST_CASE(NAME("ADD  I,  VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF01E | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("ADD  I,  V{:X}", x));
    }
}

TEST_CASE(NAME("LD   F,  VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF029 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   F,  V{:X}", x));
    }
}

TEST_CASE(NAME("LD   B,  VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF033 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   B,  V{:X}", x));
    }
}

TEST_CASE(NAME("LD   I,  VX"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF055 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   I,  V{:X}", x));
    }
}

TEST_CASE(NAME("LD   VX,  I"), TAG) {
    for (uint8_t x = 0; x <= 0x0F; x++) {
        uint16_t instruction = 0xF065 | (x << 8);
        CAPTURE(instruction, x);
        REQUIRE(DASM(instruction) == std::format("LD   V{:X}, I", x));
    }
}

TEST_CASE(NAME("UNK  FX NN"), TAG) {
    constexpr std::array<uint8_t, 9> validValues = {
        0x07,
        0x0A,
        0x15,
        0x18,
        0x1E,
        0x29,
        0x33,
        0x55,
        0x65,
    };
    for (uint8_t x = 0; x <= 0x0F; x++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            if (std::ranges::find(validValues, nn) != validValues.end())
                continue;
            uint16_t instruction = 0xF000 | (x << 8) | nn;
            CAPTURE(instruction, x, nn);
            REQUIRE(DASM(instruction) == std::format("UNK  {:02X} {:02X}", (instruction & 0xFF00) >> 8 , (instruction & 0xFF)));
        }
    }
}
