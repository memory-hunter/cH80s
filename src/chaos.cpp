#include "SDL2/SDL.h"

#include "core/cpu.cpp"
#include "core/rom.cpp"
#include "core/display.cpp"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: Couldn't init SDL. Reason: " << SDL_GetError();
        return -1;
    }
    display display("CH80S", constants::SCREEN_WIDTH * constants::SCALE, constants::SCREEN_HEIGHT * constants::SCALE,false);
    SDL_Quit();
    return 0;
}