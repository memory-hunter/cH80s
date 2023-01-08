#include "timer.h"

timer::timer() {
    past = SDL_GetTicks();
}

void timer::update_delta_time() {
    now = SDL_GetTicks();
    delta = now - past;
    past = now;
    update_count += delta;
    frame_count += delta;
}

void timer::tick_count_up() {
    tick_count++;
}

void timer::update_fps() {
    update_count -= constants::INTERVAL;
    if (frame_count >= 1000) {
        fps = tick_count;
        tick_count = 0;
        frame_count = 0;
    }
}

bool timer::check_interval() const {
    return update_count >= constants::INTERVAL;
}

uint32_t timer::get_fps() const {
    return fps > 0 ? fps : tick_count;
}

void timer::sync() {
    SDL_Delay(constants::INTERVAL);
}

timer::~timer() = default;
