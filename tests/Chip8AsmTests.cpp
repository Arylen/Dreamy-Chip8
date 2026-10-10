#include <catch2/catch_test_macros.hpp>

#include "catch2/catch_message.hpp"
#include "core/emulation/Chip8Asm.h"

#include <cstdint>
#include <format>
#include <stdexcept>

constexpr const char* TAG = "[ASM]";
#define NAME(name) std::format("{} {}", TAG, #name)

using namespace dc8::core::emulation;

#pragma region getParts
TEST_CASE(NAME("getParts (CLS)"), TAG) {
    auto parts = detail::getParts("CLS");
    REQUIRE(parts.size() == 1);
    REQUIRE(parts.at(0) == "CLS");
}

TEST_CASE(NAME("getParts (LD V1)"), TAG) {
    auto parts = detail::getParts("LD V1");
    REQUIRE(parts.size() == 2);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
}

TEST_CASE(NAME("getParts (LD V1, V2)"), TAG) {
    auto parts = detail::getParts("LD V1, V2");
    REQUIRE(parts.size() == 3);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
}

TEST_CASE(NAME("getParts (LD V1, V2, 123)"), TAG) {
    auto parts = detail::getParts("LD V1, V2, 123");
    REQUIRE(parts.size() == 4);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
    REQUIRE(parts.at(3) == "123");
}

TEST_CASE(NAME("getParts with extra spaces (LD     V1,  V2,    123)"), TAG) {
    auto parts = detail::getParts("LD     V1,  V2,    123");
    REQUIRE(parts.size() == 4);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
    REQUIRE(parts.at(3) == "123");
}

TEST_CASE(NAME("getParts with tab characters (LD\\tV1,\\tV2,\\t123)"), TAG) {
    auto parts = detail::getParts("LD\tV1,\tV2,\t123");
    REQUIRE(parts.size() == 4);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
    REQUIRE(parts.at(3) == "123");
}

TEST_CASE(NAME("getParts supports lack of comma (LD V1 V2 123)"), TAG) {
    auto parts = detail::getParts("LD V1 V2 123");
    REQUIRE(parts.size() == 4);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
    REQUIRE(parts.at(3) == "123");
}

TEST_CASE(NAME("getParts strips comments (LD V1, V2, 123 ; Comment)"), TAG) {
    auto parts = detail::getParts("LD V1, V2, 123 ; Comment");
    REQUIRE(parts.size() == 4);
    REQUIRE(parts.at(0) == "LD");
    REQUIRE(parts.at(1) == "V1");
    REQUIRE(parts.at(2) == "V2");
    REQUIRE(parts.at(3) == "123");
}
#pragma endregion

#pragma region Single Instructions
TEST_CASE(NAME("CLS"), TAG) {
    auto op = assembleInstruction("CLS");
    REQUIRE(op.value().getRaw() == 0x00E0);
}

TEST_CASE(NAME("RET"), TAG) {
    auto op = assembleInstruction("RET");
    REQUIRE(op.value().getRaw() == 0x00EE);
}

TEST_CASE(NAME("SYS NNN"), TAG) {
    for (size_t i = 0; i <= 0xFFF; i++) {
        if (i == 0x0E0 || i == 0x0EE) {
            continue;
        }
        auto instruction = std::format("SYS {:03X}", i);
        CAPTURE(instruction);
        auto op = assembleInstruction(instruction);
        REQUIRE(op.value().getFamily() == 0x0);
        REQUIRE(op.value().getNNN() == i);
    }
}
TEST_CASE(NAME("SYS 0E0 - Throws"), TAG) {
    REQUIRE_THROWS_AS(assembleInstruction("SYS 0E0"), std::invalid_argument);
}

TEST_CASE(NAME("SYS 0EE - Throws"), TAG) {
    REQUIRE_THROWS_AS(assembleInstruction("SYS 0EE"), std::invalid_argument);
}

TEST_CASE(NAME("CALL NNN"), TAG) {
    for (size_t i = 0; i <= 0xFFF; i++) {
        if (i == 0x0E0 || i == 0x0EE) {
            continue;
        }
        auto instruction = std::format("CALL {:03X}", i);
        CAPTURE(instruction);
        auto op = assembleInstruction(instruction);
        REQUIRE(op.value().getFamily() == 0x2);
        REQUIRE(op.value().getNNN() == i);
    }
}

TEST_CASE(NAME("JP NNN"), TAG) {
    for (size_t i = 0; i <= 0xFFF; i++) {
        auto instruction = std::format("JP {:03X}", i);
        CAPTURE(instruction);
        auto op = assembleInstruction(instruction);
        REQUIRE(op.value().getFamily() == 0x1);
        REQUIRE(op.value().getNNN() == i);
    }
}

TEST_CASE(NAME("JP V0, NNN"), TAG) {
    for (size_t i = 0; i <= 0xFFF; i++) {
        auto instruction = std::format("JP V0, {:03X}", i);
        CAPTURE(instruction);
        auto op = assembleInstruction(instruction);
        REQUIRE(op.value().getFamily() == 0xB);
        REQUIRE(op.value().getNNN() == i);
    }
}

TEST_CASE(NAME("SE VX, VY"), TAG) {
    for (uint8_t x = 0; x <= 0xF; x++) {
        for (uint8_t y = 0; y <= 0xF; y++) {
            auto instruction = std::format("SE V{:X}, V{:X}", x, y);
            CAPTURE(instruction);
            auto op = assembleInstruction(instruction);
            auto opHex = std::format("{:04X}", op->getRaw());
            CAPTURE(opHex);
            REQUIRE(op.value().getFamily() == 0x5);
            REQUIRE(op.value().getX() == x);
            REQUIRE(op.value().getY() == y);
            REQUIRE(op.value().getN() == (uint8_t)0);
        }
    }
}

TEST_CASE(NAME("SE VX, NN"), TAG) {
    for (uint8_t x = 0; x <= 0xF; x++) {
        for (uint16_t nn = 0; nn <= 0xF; nn++) {
            auto instruction = std::format("SE V{:X}, {:02X}", x, nn);
            CAPTURE(instruction);
            auto op = assembleInstruction(instruction);
            auto resultHex = std::format("{:04X}", op->getRaw());
            CAPTURE(resultHex);
            REQUIRE(op.value().getFamily() == 0x3);
            REQUIRE(op.value().getX() == x);
            REQUIRE(op.value().getNN() == nn);
        }
    }
}

TEST_CASE(NAME("SNE VX, VY"), TAG) {
    for (uint8_t x = 0; x <= 0xF; x++) {
        for (uint8_t y = 0; y <= 0xF; y++) {
            auto instruction = std::format("SNE V{:X}, V{:X}", x, y);
            CAPTURE(instruction);
            auto op = assembleInstruction(instruction);
            auto opHex = std::format("{:04X}", op->getRaw());
            CAPTURE(opHex);
            REQUIRE(op.value().getFamily() == 0x9);
            REQUIRE(op.value().getX() == x);
            REQUIRE(op.value().getY() == y);
            REQUIRE(op.value().getN() == (uint8_t)0);
        }
    }
}

TEST_CASE(NAME("SNE VX, NN"), TAG) {
    for (uint8_t x = 0; x <= 0xF; x++) {
        for (uint16_t nn = 0; nn <= 0xF; nn++) {
            auto instruction = std::format("SNE V{:X}, {:02X}", x, nn);
            CAPTURE(instruction);
            auto op = assembleInstruction(instruction);
            auto resultHex = std::format("{:04X}", op->getRaw());
            CAPTURE(resultHex);
            REQUIRE(op.value().getFamily() == 0x4);
            REQUIRE(op.value().getX() == x);
            REQUIRE(op.value().getNN() == nn);
        }
    }
}

TEST_CASE(NAME("JP VX, NNN - Throws on non-0 register"), TAG) {
    for (uint8_t i = 1; i <= 0xF; i++) {
        REQUIRE_THROWS_AS(assembleInstruction(std::format("JP V{:X}, 123", i)), std::invalid_argument);
    }
}

TEST_CASE(NAME("Unknown Instruction"), TAG) {
    REQUIRE_THROWS_AS(assembleInstruction("GOBBLE"), std::invalid_argument);
}

#pragma endregion
