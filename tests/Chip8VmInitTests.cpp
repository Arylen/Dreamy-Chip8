#include <format>
#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8Consts.h"
#include "core/emulation/Chip8VM.h"

#define VM dc8::core::emulation::Chip8VM
constexpr const char* TAG = "INIT";
#define NAME(name) std::format("[{}] {}", TAG, #name)

TEST_CASE(NAME("PC == 0x200"), TAG) {
    VM vm;
    REQUIRE(vm.getPC() == dc8::core::emulation::RomStartAddress);
}

TEST_CASE(NAME("I == 0"), TAG) {
    VM vm;
    REQUIRE(vm.getI() == 0);
}

TEST_CASE(NAME("CycleCount == 0"), TAG) {
    VM vm;
    REQUIRE(vm.getCycleCount() == 0);
}

TEST_CASE(NAME("DelayTimer == 0"), TAG) {
    VM vm;
    REQUIRE(vm.getDelayTimer() == 0);
}

TEST_CASE(NAME("SoundTimer == 0"), TAG) {
    VM vm;
    REQUIRE(vm.getSoundTimer() == 0);
}

TEST_CASE(NAME("Memory == 0 (excl. font"), TAG) {
    constexpr uint8_t EXPECTED = 0;

    constexpr uint16_t FONT_START = dc8::core::emulation::FontStartAddress;
    constexpr uint16_t FONT_END = dc8::core::emulation::FontEndAddress;

    VM vm;
    for (size_t address = 0; address < vm.getMem().size(); address++) {
        if (address >= FONT_START && address <= FONT_END) {
            continue;
        }
        INFO(std::format("Memory Address: 0x{:04X}", address));
        CAPTURE(address, EXPECTED);
        REQUIRE(vm.getMem()[address] == EXPECTED);
    }
}

TEST_CASE(NAME("Memory has font"), TAG) {
    constexpr std::array<uint8_t, 80> FONT_DATA = dc8::core::emulation::FontData;
    constexpr uint16_t FONT_START = dc8::core::emulation::FontStartAddress;
    constexpr uint16_t FONT_END = dc8::core::emulation::FontEndAddress;

    VM vm;
    for (size_t address = FONT_START; address < FONT_END; address++) {
        size_t arrayIdx = address - FONT_START;
        uint8_t expected = FONT_DATA[arrayIdx];
        INFO(std::format("Memory Address: 0x{:04X}", address));
        CAPTURE(address, arrayIdx, expected);
        REQUIRE(vm.getMem()[address] == expected);
    }
}
