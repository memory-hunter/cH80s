#ifndef CH80S_INPUT_H
#define CH80S_INPUT_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class input {
private:
    input();

    ~input();

    static input *instance;

    const Uint8 *current_keyboard_state;
    Uint8 *previous_keyboard_state;

public:
    static input *getInstance();

    bool key_pressed(SDL_Scancode sc);

    void update();

    void handle_input(uint8_t *keys);
};

#endif //CH80S_INPUT_H
