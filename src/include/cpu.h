#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#pragma once

#include <cstring>
#include <ctime>
#include <random>
#include <ios>
#include <iostream>
#include <array>

#include "rom.h"
#include "data.h"

class cpu {

private:
    std::array<uint8_t, info::MEMORY_SIZE> memory{};

    std::array<uint8_t, 16> v{};
    std::array<uint16_t, 16> stack{};

    uint16_t index{};
    uint16_t pc{};
    uint16_t sp{};
    uint16_t opcode{};

    uint8_t dt{};
    uint8_t st{};

    cpu();

    static cpu *instance;

    std::default_random_engine generator;

    std::uniform_int_distribution<> distribution;

public:
    ~cpu();

    cpu(const cpu &) = delete;

    void operator=(const cpu &) = delete;

    static cpu *getInstance();

    std::array<uint32_t, info::SCREEN_HEIGHT * info::SCREEN_WIDTH> display{};
    std::array<uint8_t, 16> keys{};

    bool draw_flag{};
    bool debug = true;

    void log();

    void load_rom(rom *rom);

    void fetch();

    void execute();

    void update_timers();

    void cycle();

    void clear_display();

    void ret();

    void call();

    void skip();

    void jump();

    void gen_random();

    void draw();

    void illegal() const;
};

#endif //CHIP8_CPU_H