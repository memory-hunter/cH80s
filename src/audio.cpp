#include "audio.h"

namespace waves {
    uint16_t square(uint32_t time, int32_t rate, int32_t freq, double amp) {
        auto ticks = rate / freq;
        double cycle = time % ticks;
        return cycle < static_cast<double>(ticks) / 2 ? static_cast<uint16_t>(INT_FAST16_MAX * amp) : 0;
    }
}

audio::audio() : audio(info::DEFAULT_FREQUENCY, info::DEFAULT_SAMPLE_RATE, info::DEFAULT_AMP) {}

audio::audio(int32_t freq, int32_t rt, int32_t amp) {
    frequency = freq;
    sample_rate = rt;
    amplitude = amp;
    SDL_zero(have);
    SDL_zero(want);
    want.freq = rt;
    want.format = AUDIO_U16;
    want.channels = 1;
    want.samples = 512;
    want.callback = audio::audio_callback;
    want.userdata = this;

    device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    if (!device) {
        std::cerr << "Failed to open audio. Reason: " << SDL_GetError() << "\n";
    }
}

void audio::audio_callback(void *data, uint8_t *buffer, int length) {
    auto *current = static_cast<audio *>(data);
    auto* stream = (uint16_t*)buffer;

	for (int i = 0; i < length; i++, current->sample_index++) {
        stream[i] = waves::square(current->sample_index, current->sample_rate, current->frequency, current->amplitude);
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