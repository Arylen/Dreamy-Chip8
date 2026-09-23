#include <format>
#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8VM.h"

TEST_CASE("PC inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getPC() == 0);
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

TEST_CASE("Memory inits to all 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    uint8_t expected = 0;
    for (size_t address = 0; address < vm.getMem().size(); address++) {
        INFO(std::format("Memory Address: 0x{:04X}", address));
        CAPTURE(address, expected);
        REQUIRE(vm.getMem()[address] == expected);
    }
}
