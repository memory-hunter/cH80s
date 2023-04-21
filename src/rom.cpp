#include "rom.h"

rom::rom(std::string rom_path) : path(std::move(rom_path)) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Couldn't open file\n";
        exit(-1);
    }
    size = static_cast<size_t>(file.seekg(0, std::ios::end).tellg());
    if (size > info::MEMORY_SIZE - info::PC_START) {
        std::cerr << "Error: File is too big\n";
        exit(-1);
    }
    file.seekg(0, std::ios::beg);
    auto buffer = std::make_unique<char[]>(size);
    file.read(buffer.get(), size);
    data = std::array<uint8_t, info::MEMORY_SIZE>();
    std::copy(buffer.get(), buffer.get() + size, data.begin());
    std::cout << "Loaded ROM file: " << path.substr(path.find_last_of('\\') + 1)
              << " of size: " << size
              << " bytes." << std::endl;
    file.close();
}

rom::~rom() = default;

std::array<uint8_t, info::MEMORY_SIZE> rom::get_data() const {
    return data;
}

uint32_t rom::get_size() const {
    return size;
}
