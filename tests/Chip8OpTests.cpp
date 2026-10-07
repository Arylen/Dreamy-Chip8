#include <catch2/catch_test_macros.hpp>
#include "core/emulation/Chip8Op.h"

#define OP dc8::core::emulation::Chip8Op
constexpr const char* TAG = "DECODE";
#define NAME(name) std::format("[{}] {}", TAG, #name)

#pragma region Getters
TEST_CASE(NAME("Get X"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getX() == 0x2);
}

TEST_CASE(NAME("Get Y"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getY() == 0x3);
}

TEST_CASE(NAME("Get N"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getN() == 0x4);
}

TEST_CASE(NAME("Get NN"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getNN() == 0x34);
}

TEST_CASE(NAME("Get NNN"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getNNN() == 0x234);
}

TEST_CASE(NAME("Get Hi Byte"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getHi() == 0x12);
}

TEST_CASE(NAME("Get Lo Byte"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getLo() == 0x34);
}

TEST_CASE(NAME("Get Family"), TAG) {
    const dc8::core::emulation::Chip8Op op(0x1234);
    REQUIRE(op.getFamily() == 0x1);
}
#pragma endregion

#pragma region Setters
TEST_CASE(NAME("Set X"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setX(0xA);
    REQUIRE(op.getRaw() == 0x1A34);
}

TEST_CASE(NAME("Set X masks overflow"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setX(0x1A);
    REQUIRE(op.getRaw() == 0x1A34);
}

TEST_CASE(NAME("Set Y"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setY(0xA);
    REQUIRE(op.getRaw() == 0x12A4);
}

TEST_CASE(NAME("Set Y masks overflow"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setY(0x1A);
    REQUIRE(op.getRaw() == 0x12A4);
}

TEST_CASE(NAME("Set N"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setN(0xA);
    REQUIRE(op.getRaw() == 0x123A);
}

TEST_CASE(NAME("Set N masks overflow"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setN(0x1A);
    REQUIRE(op.getRaw() == 0x123A);
}

TEST_CASE(NAME("Set NN"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setNN(0xAB);
    REQUIRE(op.getRaw() == 0x12AB);
}

TEST_CASE(NAME("Set NNN"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setNNN(0xABC);
    REQUIRE(op.getRaw() == 0x1ABC);
}

TEST_CASE(NAME("Set NNN masks overflow"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setNNN(0xFABC);
    REQUIRE(op.getRaw() == 0x1ABC);
}

TEST_CASE(NAME("Set Hi Byte"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setHi(0xAB);
    REQUIRE(op.getRaw() == 0xAB34);
}

TEST_CASE(NAME("Set Lo Byte"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setLo(0xAB);
    REQUIRE(op.getRaw() == 0x12AB);
}

TEST_CASE(NAME("Set Family"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setFamily(0xA);
    REQUIRE(op.getRaw() == 0xA234);
}

TEST_CASE(NAME("Set Family masks overflow"), TAG) {
    dc8::core::emulation::Chip8Op op(0x1234);
    op.setFamily(0x1A);
    REQUIRE(op.getRaw() == 0xA234);
}
#pragma endregion
