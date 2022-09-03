#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#pragma once

#include <cstring>
#include <ctime>
#include <random>
#include <ios>
#include <iostream>

#include "rom.h"
#include "data.h"


class cpu {
private:
    uint8_t memory[constants::MEMORY_SIZE]{};
    uint8_t v[16]{};
    uint16_t stack[16]{};

    uint16_t index{};
    uint16_t pc{};
    uint16_t sp{};
    uint16_t opcode{};

    uint8_t dt{};
    uint8_t st{};

    cpu();

    ~cpu();

    static cpu *instance;

    void init();

    std::default_random_engine generator;

    std::uniform_int_distribution<> distribution;

public:
    static cpu *getInstance();

    uint32_t display[constants::SCREEN_HEIGHT * constants::SCREEN_WIDTH]{};
    uint8_t keys[16]{};
    bool draw_flag{};

    void load_rom(rom &rom);

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