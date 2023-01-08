#ifndef CHIP8_ROM_H
#define CHIP8_ROM_H

#pragma once

#include <string>
#include "data.h"

#include <utility>
#include <fstream>
#include <iostream>
#include <array>

class rom {
private:
    std::string path;
    std::array<uint8_t, info::MEMORY_SIZE> data{};
    uint32_t size{};

public:
    explicit rom(const std::string &rom_path);

    ~rom();

    const std::string &get_path() const;

    std::array<uint8_t, info::MEMORY_SIZE> get_data() const;

    uint32_t get_size() const;

    void set_path(const std::string &path);
};

#endif //CHIP8_ROM_H