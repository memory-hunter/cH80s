#ifndef CHIP8_TIMER_H
#define CHIP8_TIMER_H

#pragma once

#include <cstdint>
#include <SDL2/SDL_timer.h>
#include "data.h"
#include "display.h"
#include "cpu.h"

class timer {
private:
    uint32_t now{};
    uint32_t past{};
    uint32_t delta{};

    uint32_t update_count{};
    uint32_t frame_count{};
    uint32_t tick_count{};
    uint32_t fps{};

    double speed_multiplier{};

public:
    timer();

    ~timer();

    void update_delta_time();

    void update_fps(display &display);

    void tick_count_up();

    void set_speed_multiplier(double speedMultiplier);

    void update_timers(const std::shared_ptr<cpu>& cpu) const;

    bool check_interval(display &display) const;

    static void sync(display &display);

    double get_speed_multiplier() const;

    uint32_t get_fps() const;
};

#endif //CHIP8_TIMER_H