#include "core/cpu.h"
#include "core/rom.h"

int main(int argc, char *argv[]) {
    cpu *cpu = cpu::getInstance();
    cpu->init();
    if (argc != 1) {
        std::cerr << "Usage: chaos.exe <rom_dir>" << std::endl;
        return -1;
    }
    rom rom(argv[1]);
    cpu->load_rom(rom);
    while(true){
        cpu->cycle();
    }
}