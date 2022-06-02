#pragma once

#include <string>
#include "../data/data.h"

#include <utility>
#include <fstream>
#include <iostream>

class rom {
private:
    std::string path;
    char *data{};
    uint32_t size{};

public:
    explicit rom(const std::string &path);

    ~rom();

    const std::string &getPath() const;

    char *getData() const;

    uint32_t getSize() const;

    void setPath(const std::string &path);
};