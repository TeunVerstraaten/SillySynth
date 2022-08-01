//
// Created by pc on 12-5-22.
//

#ifndef SYNTH_OSCILLATOR_H
#define SYNTH_OSCILLATOR_H

#include "LrBuffer.h"

#include <cstddef>

namespace view {
    class MainWindow;
}

namespace audio {
    class Oscillator {
        friend view::MainWindow;

        struct LeftRightChannel {
            float left, right;
        };

      public:
        enum OSC_TYPE { SINE, SAW, TRIANGLE, SQUARE };

        Oscillator();

        //        void                          fillBuffer(size_t frames);
        LeftRightChannel   next();
        void               setActive(bool active);
        [[nodiscard]] bool active() const;
        void               advance(float dt);
        //        [[nodiscard]] const LrBuffer& lrBuffer() const;

      private:
        Oscillator::LeftRightChannel addVoices();
        static LeftRightChannel      getPanCoefficients(float pan);

        //        LrBuffer d_lrBuffer{};
        float    d_wavePosition = 0.0f;
        bool     d_active       = true;
        float    d_volume       = 1.0f;
        float    d_pan          = 0;
        int      d_pitch        = 0;
        int      d_voices       = 1;
        float    d_width        = 0.0f;
        OSC_TYPE d_type         = SINE;
    };
} // namespace audio

#endif // SYNTH_OSCILLATOR_H
