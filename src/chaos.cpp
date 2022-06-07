#include "SDL2/SDL.h"

#include "cpu.cpp"
#include "rom.cpp"
#include "display.cpp"
#include "timer.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: Couldn't init SDL. Reason: " << SDL_GetError();
        return -1;
    }
    else{
        std::cout << "SDL initialized" << std::endl;
    }

    display display;
    cpu* cpu = cpu::getInstance();
    timer timer;
    rom rom{"test.ch8"};

    cpu->load_rom(rom);

    bool running = true;
    while (running) {
        cpu->cycle();
        timer.update_delta_time();
        while(timer.check_interval()) {
            timer.update_fps();
            timer.tick_count_up();
        }
        display.clear();
        display.render(cpu->display);
        timer::sync();
        std::cout << timer.getFps() << std::endl;
    }
    SDL_Quit();
    return 0;
}