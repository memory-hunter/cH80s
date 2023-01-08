#include <SDL2/SDL.h>

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
    rom *game = new rom(argv[1]);

    SDL_Event event;

    cpu->load_rom(game);

    cpu->debug = false;

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
        while (timer.check_interval(display)) {
            timer.update_fps(display);
            timer.tick_count_up();
            input->update();
        }
        input->handle_input(cpu->keys);
        cpu->cycle();
        display.render(cpu->display);
        timer::sync(display);
        display.change_name("CH80S - " + std::to_string(timer.get_fps()) + " FPS");
    }

    delete input;
    delete game;
    delete cpu;

    SDL_Quit();
    return 0;
}