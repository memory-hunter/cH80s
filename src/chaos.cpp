#include "SDL2/SDL.h"

#include "cpu.h"
#include "rom.h"
#include "display.h"
#include "timer.h"
#include "input.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: Couldn't init SDL. Reason: " << SDL_GetError();
        return -1;
    }

    display display;
    cpu *cpu = cpu::getInstance();
    input *input = input::getInstance();
    timer timer;
    rom rom{"pong.ch8"};

    SDL_Event event;

    cpu->load_rom(rom);

    bool running = true;
    while (running) {
        if (input->key_pressed(SDL_SCANCODE_ESCAPE)) {
            running = false;
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        timer.update_delta_time();
        while (timer.check_interval()) {
            timer.update_fps();
            timer.tick_count_up();
            input->update();
        }
        input->handle_input(cpu->keys);
        cpu->cycle();
        display.render(cpu->display);
        timer::sync();
        std::cout << timer.getFps() << std::endl;
    }
    SDL_Quit();
    return 0;
}