//
// Created by pc on 13-5-22.
//

#include "SoundEngine.h"

#include "Oscillator.h"

#include <algorithm>
#include <iostream>

namespace audio {

    SoundEngine::SoundEngine() {
        if (d_scopedPaHandler.result() != paNoError) {
            std::cerr << "An error occurred while using the portaudio stream\n";
            std::cerr << "Error number: " << d_scopedPaHandler.result() << "\n";
            std::cerr << "Error message: " << Pa_GetErrorText(d_scopedPaHandler.result()) << "\n";
            return;
        }

        if (not open(Pa_GetDefaultOutputDevice()))
            std::cerr << "Cannot open sine\n";

        for (size_t i = 0; i != NUM_OSCILLATORS; ++i)
            for (size_t j = 0; j != NUM_BUSSES + 1; ++j)
                d_oscillatorSends[i][j] = j == NUM_BUSSES ? 1.0f : 0.0f;

        for (size_t i = 1; i != NUM_OSCILLATORS; ++i)
            d_oscillators[i].setActive(false);

        d_master.effects()[0] = fx::Effect{fx::Distortion{fx::Distortion::TYPE::POWER, 0.5f}};
    }

    SoundEngine::~SoundEngine() {
        close();
    }

    bool SoundEngine::play() {
        return start();
    }

    std::array<Oscillator, NUM_OSCILLATORS>& SoundEngine::oscillators() {
        return d_oscillators;
    }

    std::array<std::array<float, NUM_BUSSES + 1>, NUM_OSCILLATORS>& SoundEngine::oscillatorSends() {
        return d_oscillatorSends;
    }

    bool SoundEngine::open(PaDeviceIndex index) {
        PaStreamParameters outputParameters;

        outputParameters.device = index;
        if (outputParameters.device == paNoDevice)
            return false;

        const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
        if (pInfo != nullptr)
            printf("Output device name: '%s'\r", pInfo->name);

        outputParameters.channelCount              = 2;         /* stereo output */
        outputParameters.sampleFormat              = paFloat32; /* 32 bit floating point output */
        outputParameters.suggestedLatency          = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;

        PaError err = Pa_OpenStream(&d_stream,
                                    nullptr, /* no input */
                                    &outputParameters,
                                    SAMPLE_RATE,
                                    paFramesPerBufferUnspecified,
                                    paClipOff, /* we won't output out of range samples so don't bother clipping them */
                                    &SoundEngine::paCallback,
                                    this /* Using 'this' for userData so we can cast to Oscillator* in paCallback method */
        );

        if (err != paNoError) {
            /* Failed to open stream to device !!! */
            return false;
        }

        err = Pa_SetStreamFinishedCallback(d_stream, &SoundEngine::paStreamFinished);

        if (err != paNoError) {
            Pa_CloseStream(d_stream);
            d_stream = nullptr;

            return false;
        }

        return true;
    }

    bool SoundEngine::close() {
        if (d_stream == nullptr)
            return false;

        PaError err = Pa_CloseStream(d_stream);
        d_stream    = nullptr;

        return (err == paNoError);
    }

    bool SoundEngine::start() {
        if (d_stream == nullptr)
            return false;

        PaError err = Pa_StartStream(d_stream);

        return (err == paNoError);
    }

    bool SoundEngine::stop() {
        if (d_stream == nullptr)
            return false;

        PaError err = Pa_StopStream(d_stream);

        return (err == paNoError);
    }

    int SoundEngine::paCallbackMethod(void*                                            outputBuffer,
                                      unsigned long                                    framesPerBuffer,
                                      [[maybe_unused]] const PaStreamCallbackTimeInfo* timeInfo,
                                      [[maybe_unused]] PaStreamCallbackFlags           statusFlags) {
        auto* out = (float*)outputBuffer;

        for (size_t i = 0; i < framesPerBuffer; i++) {
            if (d_currentIndex == 0)
                refillMasterBus();

            *out++ = 0.2f * d_master.lrBuffer().leftBuffer[d_currentIndex];
            *out++ = 0.2f * d_master.lrBuffer().rightBuffer[d_currentIndex];

            ++d_currentIndex;
            d_currentIndex %= LOOK_AHEAD;
        }

        return paContinue;
    }

    int SoundEngine::paCallback([[maybe_unused]] const void*    inputBuffer,
                                void*                           outputBuffer,
                                unsigned long                   framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeInfo,
                                PaStreamCallbackFlags           statusFlags,
                                void*                           userData) {
        return ((SoundEngine*)userData)->paCallbackMethod(outputBuffer, framesPerBuffer, timeInfo, statusFlags);
    }

    void SoundEngine::paStreamFinishedMethod() {
    }

    void SoundEngine::paStreamFinished(void* userData) {
        return ((SoundEngine*)userData)->paStreamFinishedMethod();
    }

    void SoundEngine::refillMasterBus() {
        std::for_each(d_busses.begin(), d_busses.end(), [](Bus& bus) { bus.reset(); });
        d_master.reset();
        std::array<LrBuffer, NUM_OSCILLATORS> oscBuffers{};
        for (size_t t = 0; t != LOOK_AHEAD; ++t) {
            for (size_t osc = 0; osc != NUM_OSCILLATORS; ++osc) {
                if (d_oscillators[osc].active()) {
                    const auto val                 = d_oscillators[osc].next();
                    oscBuffers[osc].leftBuffer[t]  = val.left;
                    oscBuffers[osc].rightBuffer[t] = val.right;
                }
            }
            for (size_t osc = 0; osc != NUM_OSCILLATORS; ++osc) {
                float dt = 1.0f;
                for (size_t modOsc = 0; modOsc != NUM_OSCILLATORS; ++modOsc)
                    if (d_oscillators[modOsc].active())
                        dt += oscBuffers[modOsc].leftBuffer[t] * d_fmMatrix[osc][modOsc];

                d_oscillators[osc].advance(dt);
            }
        }

        for (size_t osc = 0; osc != NUM_OSCILLATORS; ++osc)
            if (d_oscillators[osc].active()) {
                d_master.add(oscBuffers[osc], d_oscillatorSends[osc][NUM_BUSSES]);
                for (size_t bus = 0; bus != NUM_BUSSES; ++bus)
                    d_busses[bus].add(oscBuffers[osc], d_oscillatorSends[osc][bus]);
            }

        std::for_each(d_busses.begin(), d_busses.end(), [](Bus& bus) { bus.process(); });
        for (const auto& bus : d_busses)
            d_master.add(bus.lrBuffer(), 1.0f);

        d_master.process();
    }

    std::array<Bus, NUM_BUSSES>& SoundEngine::busses() {
        return d_busses;
    }

    Bus& SoundEngine::master() {
        return d_master;
    }

    Bus& SoundEngine::getBus(size_t index) {
        if (index == NUM_BUSSES)
            return d_master;
        else
            return d_busses[index];
    }

 std::array<std::array<float, NUM_OSCILLATORS>, NUM_OSCILLATORS>& SoundEngine::fmMatrix() {
        return d_fmMatrix;
    }

} // namespace audio