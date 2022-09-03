#include "input.h"

input::input() {
    current_keyboard_state = SDL_GetKeyboardState(nullptr);
    previous_keyboard_state = new Uint8[SDL_NUM_SCANCODES];
    memcpy(previous_keyboard_state, current_keyboard_state, SDL_NUM_SCANCODES);
}

input::~input() {
    delete[] current_keyboard_state;
    delete[] previous_keyboard_state;
}

input* input::instance = nullptr;

input *input::getInstance() {
    if (instance == nullptr) {
        instance = new input();
    }
    return instance;
}

bool input::key_pressed(SDL_Scancode sc) {
    return current_keyboard_state[sc] && !previous_keyboard_state[sc];
}

void input::update() {
    memcpy(previous_keyboard_state, current_keyboard_state, SDL_NUM_SCANCODES);
    current_keyboard_state = SDL_GetKeyboardState(nullptr);
}

void input::handle_input(uint8_t *keys) {
    if (key_pressed(SDL_SCANCODE_1)) {
        keys[0x1] = 1;
    }
    if (key_pressed(SDL_SCANCODE_2)) {
        keys[0x2] = 1;
    }
    if (key_pressed(SDL_SCANCODE_3)) {
        keys[0x3] = 1;
    }
    if (key_pressed(SDL_SCANCODE_4)) {
        keys[0xC] = 1;
    }
    if (key_pressed(SDL_SCANCODE_Q)) {
        keys[0x4] = 1;
    }
    if (key_pressed(SDL_SCANCODE_W)) {
        keys[0x5] = 1;
    }
    if (key_pressed(SDL_SCANCODE_E)) {
        keys[0x6] = 1;
    }
    if (key_pressed(SDL_SCANCODE_R)) {
        keys[0xD] = 1;
    }
    if (key_pressed(SDL_SCANCODE_A)) {
        keys[0x7] = 1;
    }
    if (key_pressed(SDL_SCANCODE_S)) {
        keys[0x8] = 1;
    }
    if (key_pressed(SDL_SCANCODE_D)) {
        keys[0x9] = 1;
    }
    if (key_pressed(SDL_SCANCODE_F)) {
        keys[0xE] = 1;
    }
    if (key_pressed(SDL_SCANCODE_Z)) {
        keys[0xA] = 1;
    }
    if (key_pressed(SDL_SCANCODE_X)) {
        keys[0x0] = 1;
    }
    if (key_pressed(SDL_SCANCODE_C)) {
        keys[0xB] = 1;
    }
    if (key_pressed(SDL_SCANCODE_V)) {
        keys[0xF] = 1;
    }
    for(int i = 0; i < 16; i++) {
        if (keys[i] == 1) {
            std::cout << "Key " << i << " pressed" << std::endl;
        }
    }
}
