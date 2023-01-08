#include "rom.h"

rom::rom(const std::string &rom_path) {
    path = rom_path;
    std::fstream file(rom::path, std::ios::in);
    if (!file) {
        std::cerr << "Error: Couldn't open file\n";
        exit(-1);
    }
    size = file.seekg(0, std::ios::end).tellg();
    if (size > info::MEMORY_SIZE - info::PC_START) {
        std::cerr << "Error: File is too big\n";
        exit(-1);
    }
    file.seekg(0, std::ios::beg);
    char *buffer = new char[size];
    file.read(buffer, size);
    data = std::array<uint8_t, info::MEMORY_SIZE>();
    std::copy(buffer, buffer + size, data.begin());
    delete[] buffer;
    std::cout << "Loaded ROM file: " << rom::path.substr(rom::path.find_last_of('\\') + 1)
              << " of size: " << size
              << " bytes." << std::endl;
    file.close();
}

const std::string &rom::get_path() const {
    return path;
}

void rom::set_path(const std::string &new_path) {
    path = new_path;
}

rom::~rom() = default;

std::array<uint8_t, info::MEMORY_SIZE> rom::get_data() const {
    return data;
}

uint32_t rom::get_size() const {
    return size;
}
