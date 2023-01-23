#ifndef CH80S_AUDIO_H
#define CH80S_AUDIO_H

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "data.h"

class audio {

    static int32_t sample_rate, frequency;
    static uint64_t samples_played;

    SDL_AudioSpec have{}, want{};
    SDL_AudioDeviceID device{};

    static void audio_callback(void *data, uint8_t *buffer, int length);

    void play() const;

    void stop() const;

public:
    audio();

    explicit audio(int32_t freq);

    audio(int32_t freq, int32_t rt);

    ~audio();

    void play_sound(uint32_t duration);
};


#endif //CH80S_AUDIO_H
