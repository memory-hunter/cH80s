#include <SDL2/SDL.h>

#include "cpu.h"
#include "rom.h"
#include "display.h"
#include "timer.h"
#include "input.h"
#include "audio.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error: Couldn't initialize SDL. Reason: " << SDL_GetError();
        return -1;
    }

    std::unique_ptr<display> display = std::make_unique<class display>();
    std::shared_ptr<cpu> cpu = cpu::getInstance();
    std::unique_ptr<timer> timer = std::make_unique<class timer>();
    std::unique_ptr<input> input = std::make_unique<class input>();
    std::unique_ptr<audio> audio = std::make_unique<class audio>();

    if (argc < 2) {
        std::cout << "Usage: cH80s.exe <ROM file>\n";
        return -1;
    }

    std::shared_ptr<rom> game = std::make_shared<rom>(argv[1]);

    SDL_Event event;

    cpu->set_sound(*audio);
    cpu->load_rom(game);
    cpu->debug = true;

    bool running = true;

    timer->set_speed_multiplier(5);

    while (running) {
        if (input->key_pressed(SDL_SCANCODE_ESCAPE)) {
            running = false;
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        timer->update_delta_time();
        while (timer->check_interval(*display)) {
            timer->update_fps(*display);
            timer->tick_count_up();
            input->update();
        }
        input->handle_input(cpu->keys);
        for (int i = 0; i < timer->get_speed_multiplier(); ++i) {
            cpu->cycle();
        }
        timer->update_timers(cpu);
        display->render(cpu->display);
        timer::sync(*display);
        display->change_name("CH80S - " + std::to_string(timer->get_fps()) + " FPS");
    }

    SDL_Quit();
    return 0;
}
