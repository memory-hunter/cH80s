#include "timer.h"

timer::timer() {
    past = SDL_GetTicks();
    speed_multiplier = 2;
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

void timer::update_fps(display &display) {
    update_count -= display.interval;
    if (frame_count >= 1000) {
        fps = tick_count;
        tick_count = 0;
        frame_count = 0;
    }
}

bool timer::check_interval(display &display) const {
    return update_count >= display.interval;
}

uint32_t timer::get_fps() const {
    return fps > 0 ? fps : tick_count;
}

void timer::sync(display &display) {
    SDL_Delay(display.interval);
}

void timer::set_speed_multiplier(double speedMultiplier) {
    speed_multiplier = speedMultiplier;
}

double timer::get_speed_multiplier() const {
    return speed_multiplier;
}

void timer::update_timers(const std::shared_ptr<cpu> &cpu) const {
    if (delta >= info::SOUND_CLOCK) {
        cpu->update_timers();
    }
}

timer::~timer() = default;