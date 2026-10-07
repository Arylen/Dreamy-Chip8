#include <catch2/catch_test_macros.hpp>

#include "core/emulation/Chip8Asm.h"

#include <format>

constexpr const char* TAG = "[ASM]";
#define NAME(name) std::format("{} {}", TAG, #name)

using namespace dc8::core::emulation;

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
