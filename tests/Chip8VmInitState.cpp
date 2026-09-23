#include <catch2/catch_test_macros.hpp>
#include "core/emulation/Chip8VM.h"

TEST_CASE("PC Inits to 0", "[Chip8VM]") {
    dc8::core::emulation::Chip8VM vm;
    REQUIRE(vm.getPC() == 0);
}
