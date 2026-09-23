#include <catch2/catch_test_macros.hpp>
#include "core/emulation/Chip8Op.h"

TEST_CASE("Chip8Op Decodes X", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getX() == 0x2);
}

TEST_CASE("Chip8Op Decodes Y", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getY() == 0x3);
}

TEST_CASE("Chip8Op Decodes N", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getN() == 0x4);
}
