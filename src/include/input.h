#ifndef CH80S_INPUT_H
#define CH80S_INPUT_H

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include <vector>

class input {
private:
    input();

    static input *instance;

    std::vector<uint8_t> current_keyboard_state;
    std::vector<uint8_t> previous_keyboard_state;

public:
    ~input();

    input(const input &) = delete;

    void operator=(const input &) = delete;

    static input *getInstance();

    bool key_pressed(SDL_Scancode sc);

    void update();

    void handle_input(std::array<uint8_t, 16> &keys);
};

#endif //CH80S_INPUT_H
