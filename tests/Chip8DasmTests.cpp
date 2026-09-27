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
    for (uint8_t reg = 0; reg <= 0x0F; reg++) {
        for (uint16_t nn = 0; nn <= 0xFF; nn++) {
            uint16_t instruction = 0x4000 | (reg << 8) | nn;
            CAPTURE(instruction, reg, nn);
            REQUIRE(DASM(instruction) == std::format("SNE  V{:X}, {:02X}", reg, nn));
        }
    }
}
