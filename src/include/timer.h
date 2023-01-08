#ifndef CHIP8_TIMER_H
#define CHIP8_TIMER_H

#pragma once

#include <cstdint>
#include <SDL2/SDL_timer.h>
#include "data.h"
#include "display.h"

class timer {
private:
    uint32_t now{};
    uint32_t past{};
    uint32_t delta{};

    uint32_t update_count{};
    uint32_t frame_count{};
    uint32_t tick_count{};
    uint32_t fps{};

    uint32_t speed_multiplier{};

public:
    uint32_t get_fps() const;

public:
    timer();

    ~timer();

    void update_delta_time();

    void update_fps(display &display);

    void tick_count_up();

    void set_speed_multiplier(uint32_t speedMultiplier);

    bool check_interval(display &display) const;

    static void sync(display &display);

    uint32_t get_speed_multiplier() const;
};

#endif //CHIP8_TIMER_H