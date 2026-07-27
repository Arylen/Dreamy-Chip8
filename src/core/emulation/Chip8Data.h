#pragma once

#include <cstdint>
#include <vector>

namespace dc8::core::emulation {
    // Display stuffs
    constexpr int LoResWidth  = 64;
    constexpr int LoResHeight = 32;
    constexpr int HiResWidth  = 128;
    constexpr int HiResHeight = 64;
    constexpr int MaxBufferSize = HiResWidth * HiResHeight;

    constexpr uint16_t RomStartAddress  = 0x200;
    constexpr uint16_t FontStartAddress = 0x50;

    constexpr std::vector<uint8_t> FontData = {

    };
}
