#include <format>
#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8Consts.h"
#include "core/emulation/Chip8VM.h"

TEST_CASE("PC inits to 0x200", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getPC() == dc8::core::emulation::RomStartAddress);
}

TEST_CASE("I inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getI() == 0);
}

TEST_CASE("CycleCount inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getCycleCount() == 0);
}

TEST_CASE("DelayTimer inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getDelayTimer() == 0);
}

TEST_CASE("SoundTimer inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getSoundTimer() == 0);
}

TEST_CASE("Memory inits to all 0, except font", "[Chip8VM]") {
    constexpr uint8_t EXPECTED = 0;

    constexpr uint16_t FONT_START = dc8::core::emulation::FontStartAddress;
    constexpr uint16_t FONT_END = dc8::core::emulation::FontEndAddress;

    dc8::core::emulation::Chip8VM vm;
    for (size_t address = 0; address < vm.getMem().size(); address++) {
        if (address >= FONT_START && address <= FONT_END) {
            continue;
        }
        INFO(std::format("Memory Address: 0x{:04X}", address));
        CAPTURE(address, EXPECTED);
        REQUIRE(vm.getMem()[address] == EXPECTED);
    }
}

TEST_CASE("Memory at init contains font data", "[Chip8VM]") {
    constexpr std::array<uint8_t, 80> FONT_DATA = dc8::core::emulation::FontData;
    constexpr uint16_t FONT_START = dc8::core::emulation::FontStartAddress;
    constexpr uint16_t FONT_END = dc8::core::emulation::FontEndAddress;

    dc8::core::emulation::Chip8VM vm;
    for (size_t address = FONT_START; address < FONT_END; address++) {
        size_t arrayIdx = address - FONT_START;
        uint8_t expected = FONT_DATA[arrayIdx];
        INFO(std::format("Memory Address: 0x{:04X}", address));
        CAPTURE(address, arrayIdx, expected);
        REQUIRE(vm.getMem()[address] == expected);
    }
}
