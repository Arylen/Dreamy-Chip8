#include <catch2/catch_test_macros.hpp>
#include "core/emulation/Chip8Op.h"

#define OP dc8::core::emulation::Chip8Op
constexpr const char* TAG = "DECODE";
#define NAME(name) std::format("[{}] {}", TAG, #name)

TEST_CASE(NAME("X"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getX() == 0x2);
}

TEST_CASE(NAME("Y"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getY() == 0x3);
}

TEST_CASE(NAME("N"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getN() == 0x4);
}

TEST_CASE(NAME("NN"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getNN() == 0x34);
}

TEST_CASE(NAME("NNN"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getNNN() == 0x234);
}

TEST_CASE(NAME("Hi Byte"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getHi() == 0x12);
}

TEST_CASE(NAME("Lo Byte"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getLo() == 0x34);
}

TEST_CASE(NAME("Family"), TAG) {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getFamily() == 0x1);
}
