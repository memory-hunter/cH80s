#include <cstdint>
#include <SDL2/SDL_timer.h>
#include "data.h"

class timer {
private:
    uint32_t now{};
    uint32_t past{};
    uint32_t delta{};

    uint32_t update_count{};
    uint32_t frame_count{};
    uint32_t tick_count{};
    uint32_t fps{};
public:
    uint32_t getFps() const;

public:
    timer();
    ~timer();
    void update_delta_time();
    void update_fps();
    void tick_count_up();
    bool check_interval() const;
    static void sync();
};