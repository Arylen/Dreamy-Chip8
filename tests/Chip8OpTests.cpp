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

TEST_CASE("Chip8Op Decodes NN", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getNN() == 0x34);
}

TEST_CASE("Chip8Op Decodes NNN", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getNNN() == 0x234);
}

TEST_CASE("Chip8Op Decodes Hi Byte", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getHi() == 0x12);
}

TEST_CASE("Chip8Op Decodes Lo Byte", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getLo() == 0x34);
}

TEST_CASE("Chip8Op Decodes Family", "[Chip8Op]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getFamily() == 0x1);
}
