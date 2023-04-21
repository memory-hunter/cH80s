#ifndef CHIP8_ROM_H
#define CHIP8_ROM_H

#pragma once

#include <string>
#include "data.h"

#include <utility>
#include <fstream>
#include <iostream>
#include <array>
#include <memory>
#include <utility>

class rom {
private:
    std::string path;
    std::array<uint8_t, info::MEMORY_SIZE> data{};
    uint32_t size{};

public:
    explicit rom(std::string rom_path);

    ~rom();

    [[nodiscard]] std::array<uint8_t, info::MEMORY_SIZE> get_data() const;

    [[nodiscard]] uint32_t get_size() const;
};

#endif //CHIP8_ROM_H