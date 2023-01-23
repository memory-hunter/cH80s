#include "audio.h"

namespace sounds {
    uint8_t square(uint32_t time, int32_t rate, int32_t freq, double amp) {
        auto ticks = rate / freq;
        double cycle = time % ticks;
        return cycle < static_cast<double>(ticks) / 2 ? static_cast<uint8_t>(INT_FAST16_MAX * amp) : 0;
    }
}

audio::audio() : audio(info::DEFAULT_FREQUENCY, info::DEFAULT_SAMPLE_RATE) {}

audio::audio(int32_t freq) : audio(freq, info::DEFAULT_SAMPLE_RATE) {}

audio::audio(int32_t freq, int32_t rt) {
    frequency = freq;
    sample_rate = rt;
    SDL_zero(have);
    SDL_zero(want);
    want.freq = sample_rate;
    want.format = AUDIO_U8;
    want.channels = 1;
    want.samples = 256;
    want.callback = audio_callback;
    want.userdata = (void*)&samples_played;

    device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (!device) {
        std::cerr << "Failed to open audio. Reason: " << SDL_GetError() << "\n";
    }
}

void audio::audio_callback(void *data, uint8_t *buffer, int length) {
    for (int i = 0; i < length; ++i) {
        buffer[i] = sounds::square((samples_played + i) / info::DEFAULT_SAMPLE_RATE, sample_rate, frequency, 1);
        samples_played++;
    }
}

void audio::play() const {
    SDL_PauseAudioDevice(device, 0);
}

void audio::stop() const {
    SDL_PauseAudioDevice(device, 1);
}


audio::~audio() {
    SDL_CloseAudioDevice(device);
}

void audio::play_sound(uint32_t duration) {
    audio::play();
    SDL_Delay(duration);
    audio::stop();
}
