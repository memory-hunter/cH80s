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

    display(const std::string &title, int width, int height);

public:
    display();

    ~display();

    void render(uint32_t screen[constants::SCREEN_WIDTH * constants::SCREEN_HEIGHT]);

    void clear();

    SDL_Window *getWindow() const;
};


#endif //CH80S_DISPLAY_H