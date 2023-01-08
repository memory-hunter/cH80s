#ifndef CH80S_INPUT_H
#define CH80S_INPUT_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class input {
private:
    input();

    static input *instance;

    const uint8_t *current_keyboard_state;
    uint8_t *previous_keyboard_state;

public:
    ~input();

    input(const input &) = delete;

    void operator=(const input &) = delete;

    static input *getInstance();

    bool key_pressed(SDL_Scancode sc);

    void update();

    void handle_input(uint8_t *keys);
};

#endif //CH80S_INPUT_H
