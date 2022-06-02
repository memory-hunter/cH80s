#include "rom.h"

rom::rom(const std::string &path) {
    this->path = path;
    std::fstream file(rom::path, std::ios::in);
    if (!file) {
        std::cerr << "Error: Couldn't open file\n";
        exit(404);
    }
    size = file.seekg(0, std::ios::end).tellg();
    if (size > constants::MEMORY_SIZE - constants::PC_START) {
        std::cerr << "Error: File is too big\n";
        exit(404);
    }
    file.seekg(0, std::ios::beg);
    data = new char[constants::MEMORY_SIZE];
    file.read(data, constants::MEMORY_SIZE);
    std::cout << "Loaded ROM file: " << rom::path.substr(rom::path.find_last_of('\\') + 1)
              << " of size: " << size
              << " bytes." << std::endl;
    file.close();
}

const std::string &rom::getPath() const {
    return path;
}

void rom::setPath(const std::string &path) {
    rom::path = path;
}

rom::~rom() {
    delete[] data;
}

char *rom::getData() const {
    return data;
}

uint32_t rom::getSize() const {
    return size;
}
