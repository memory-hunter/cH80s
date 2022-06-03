#ifndef CH80S_DISPLAY_H
#define CH80S_DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

#include "data.h"

class display {
private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Texture *texture{};

public:
    display(const std::string& title, int width, int height, bool fullscreen);
    ~display();

    void render(uint32_t screen[constants::SCREEN_WIDTH * constants::SCREEN_HEIGHT]);
    void clear();
};


#endif