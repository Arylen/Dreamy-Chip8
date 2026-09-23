#include <catch2/catch_test_macros.hpp>
#include "core/emulation/Chip8Op.h"

TEST_CASE("Opcode decodes X", "[opcode]") {
    const dc8::core::emulation::Chip8Op op {
        .raw = 0x1234,
    };

    REQUIRE(op.getX() == 0x2);
}
