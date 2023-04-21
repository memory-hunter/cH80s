#ifndef CH80S_DISPLAY_H
#define CH80S_DISPLAY_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "data.h"

class display {
private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Texture *texture{};
    SDL_DisplayMode *mode;

    display(const std::string &title, int width, int height);

public:
    display();

    ~display();

    uint32_t fps;
    uint32_t interval;

    void render(std::array<uint32_t, info::SCREEN_WIDTH * info::SCREEN_HEIGHT> &screen);

    void change_name(const std::string &name);
};


#endif //CH80S_DISPLAY_H