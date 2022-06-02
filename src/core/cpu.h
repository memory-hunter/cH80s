#pragma once

#include <cstring>
#include <ctime>
#include <random>
#include <ios>
#include <iostream>

#include "rom.h"
#include "../data/data.h"

class cpu {
private:
    uint8_t memory[constants::MEMORY_SIZE]{};
    uint8_t v[16]{};
    uint8_t keys[16]{};
    uint16_t stack[16]{};


    uint16_t index{};
    uint16_t pc{};
    uint16_t sp{};
    uint16_t opcode{};

    uint8_t dt{};
    uint8_t st{};

    cpu();

    static cpu *instance;

public:
    static cpu *getInstance();

    uint32_t display[constants::SCREEN_HEIGHT * constants::SCREEN_WIDTH]{};

    void init();

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
