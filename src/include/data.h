#ifndef CH80S_DATA_H
#define CH80S_DATA_H

#pragma once

#include <cstdint>
#include <array>

#define nnn(opcode) (opcode & 0x0fff)
#define xh(opcode) ((opcode & 0xf000) >> 12)
#define xl(opcode) ((opcode & 0x0f00) >> 8)
#define yh(opcode) ((opcode & 0x00f0) >> 4)
#define yl(opcode) (opcode & 0x000f)
#define kk(opcode) (opcode & 0x00ff)

namespace info {
    constexpr uint32_t MEMORY_SIZE = 4096;
    constexpr uint32_t PC_START = 0x200;
    constexpr uint64_t P_ON = 0xFFFFFFFF;
    constexpr uint32_t P_OFF = 0x00000000;
    constexpr uint32_t SCREEN_WIDTH = 64;
    constexpr uint32_t SCREEN_HEIGHT = 32;
    constexpr uint32_t SCALE = 10;
    constexpr uint32_t DEFAULT_FPS = 60;
    constexpr uint32_t DEFAULT_INTERVAL = 1000 / 60;
    constexpr uint32_t DEFAULT_FREQUENCY = 500;
    constexpr uint32_t DEFAULT_SAMPLE_RATE = 44100;
    constexpr uint32_t DEFAULT_AMP = 28000;
}

static std::array<uint8_t, 80> font_set =
        {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

#endif //CH80S_DATA_H
