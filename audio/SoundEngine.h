//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_SOUNDENGINE_H
#define SYNTH_SOUNDENGINE_H

#include "../include/portaudio.h"
#include "Bus.h"
#include "Oscillator.h"
#include "ScopedPaHandler.h"

#include <array>

namespace audio {
    class SoundEngine {

      public:
        SoundEngine();
        virtual ~SoundEngine();

        bool open(PaDeviceIndex index);
        bool close();
        bool start();
        bool stop();
        bool play();

        Bus&                                                             getBus(size_t index);
        Bus&                                                             master();
        std::array<Bus, NUM_BUSSES>&                                     busses();
        std::array<Oscillator, NUM_OSCILLATORS>&                         oscillators();
        std::array<std::array<float, NUM_BUSSES + 1>, NUM_OSCILLATORS>&  oscillatorSends();
        std::array<std::array<float, NUM_OSCILLATORS>, NUM_OSCILLATORS>& fmMatrix();

      private:
        void        refillMasterBus();
        int         paCallbackMethod(void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags);
        static int  paCallback(const void*                     inputBuffer,
                               void*                           outputBuffer,
                               unsigned long                   framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags           statusFlags,
                               void*                           userData);
        void        paStreamFinishedMethod();
        static void paStreamFinished(void* userData);

        PaStream*                                                       d_stream = nullptr;
        ScopedPaHandler                                                 d_scopedPaHandler;
        size_t                                                          d_currentIndex = 0;
        std::array<Oscillator, NUM_OSCILLATORS>                         d_oscillators{};
        std::array<Bus, NUM_BUSSES>                                     d_busses{};
        Bus                                                             d_master{};
        std::array<std::array<float, NUM_BUSSES + 1>, NUM_OSCILLATORS>  d_oscillatorSends{};
        std::array<std::array<float, NUM_OSCILLATORS>, NUM_OSCILLATORS> d_fmMatrix = {{{0.0f}}};
    };
} // namespace audio

#endif // SYNTH_SOUNDENGINE_H
