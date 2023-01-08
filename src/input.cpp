#include "input.h"

input::input() {
    auto current = SDL_GetKeyboardState(nullptr);
    current_keyboard_state = std::vector<uint8_t>(current, current + 322);
    previous_keyboard_state = current_keyboard_state;
}

input::~input() = default;

input* input::instance = nullptr;

input *input::getInstance() {
    if (instance == nullptr) {
        instance = new input();
    }
    return instance;
}

bool input::key_pressed(SDL_Scancode sc) {
    return current_keyboard_state[sc] && previous_keyboard_state[sc];
}

void input::update() {
    previous_keyboard_state = current_keyboard_state;
    auto current = SDL_GetKeyboardState(nullptr);
    current_keyboard_state = std::vector<uint8_t>(current, current + 322);
}

void input::handle_input(std::array<uint8_t, 16> &keys) {
    keys.fill(0);
    keys[0] = key_pressed(SDL_SCANCODE_1);
    keys[1] = key_pressed(SDL_SCANCODE_2);
    keys[2] = key_pressed(SDL_SCANCODE_3);
    keys[3] = key_pressed(SDL_SCANCODE_4);
    keys[4] = key_pressed(SDL_SCANCODE_Q);
    keys[5] = key_pressed(SDL_SCANCODE_W);
    keys[6] = key_pressed(SDL_SCANCODE_E);
    keys[7] = key_pressed(SDL_SCANCODE_R);
    keys[8] = key_pressed(SDL_SCANCODE_A);
    keys[9] = key_pressed(SDL_SCANCODE_S);
    keys[10] = key_pressed(SDL_SCANCODE_D);
    keys[11] = key_pressed(SDL_SCANCODE_F);
    keys[12] = key_pressed(SDL_SCANCODE_Z);
    keys[13] = key_pressed(SDL_SCANCODE_X);
    keys[14] = key_pressed(SDL_SCANCODE_C);
    keys[15] = key_pressed(SDL_SCANCODE_V);
}
