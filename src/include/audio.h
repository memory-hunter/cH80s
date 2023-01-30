#ifndef CH80S_AUDIO_H
#define CH80S_AUDIO_H

#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "data.h"

class audio {

    int32_t sample_rate, frequency, amplitude;
    int32_t sample_index{};

    SDL_AudioSpec have{}, want{};
    SDL_AudioDeviceID device{};

    static void audio_callback(void *data, uint8_t *buffer, int length);

public:
    audio();

    audio(int32_t freq, int32_t rt, int32_t amp);

    ~audio();

    void play() const;

    void stop() const;
};


#endif //CH80S_AUDIO_H
