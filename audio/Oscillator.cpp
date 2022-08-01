//
// Created by pc on 12-5-22.
//

#include "Oscillator.h"

#include "math.h"

#include <cmath>
#include <functional>

namespace audio {

    Oscillator::Oscillator() = default;

    Oscillator::LeftRightChannel Oscillator::addVoices() {
        static double dummy;
        float         left  = 0.0f;
        float         right = 0.0f;

        std::function<float(float)> toWave;

        switch (d_type) {
            case SINE:
                toWave = [](float f) { return std::sin(f * M_PI); };
                break;
            case SAW:
                toWave = [](float f) { return f; };
                break;
            case TRIANGLE:
                toWave = [](float f) { return 2.0f * static_cast<float>(math::sign(f)) * std::abs(f - std::floor(f + 0.5f)); };
                break;
            case SQUARE:
                toWave = [](float f) { return static_cast<float>(math::sign(f)); };
                break;
        }
        const float pitchOffset = std::pow(2.0f, static_cast<float>(d_pitch) / 12.0f);
        for (int i = 0; i != d_voices; ++i) {
            float interpolant = d_voices == 1 ? 0.0f : (static_cast<float>(2 * i) / static_cast<float>(d_voices - 1)) - 1.0f;

            const float position = 2.0f * static_cast<float>(modf(pitchOffset * 440.0f * d_wavePosition / (SAMPLE_RATE * (1 + 0.3f * interpolant * d_width)), &dummy)) - 1.0f;

            float signal = toWave(position);
            auto  panLr  = getPanCoefficients(interpolant);

            left += signal * panLr.left;
            right += signal * panLr.right;
        }
        return {left, right};
    }

    Oscillator::LeftRightChannel Oscillator::getPanCoefficients(float pan) {
        return {std::min(1.0f, 1.0f - pan), std::min(1.0f, pan + 1.0f)};
    }

    //    const LrBuffer& Oscillator::lrBuffer() const {
    //        return d_lrBuffer;
    //    }

    //    void Oscillator::fillBuffer(size_t frames) {
    //        assert(frames != 0);
    //        for (size_t i = 0; i != frames; i++) {
    //            auto lr    = addVoices();
    //            auto panLr = getPanCoefficients(d_pan);
    //
    //            d_lrBuffer.leftBuffer[i]  = d_volume * lr.left * panLr.left;
    //            d_lrBuffer.rightBuffer[i] = d_volume * lr.right * panLr.right;
    //            d_wavePosition += 1.0f;
    //        }
    //    }

    bool Oscillator::active() const {
        return d_active;
    }

    void Oscillator::setActive(bool active) {
        d_active = active;
    }

    Oscillator::LeftRightChannel Oscillator::next() {
        auto lr    = addVoices();
        auto panLr = getPanCoefficients(d_pan);

        return {d_volume * lr.left * panLr.left, d_volume * lr.right * panLr.right};
    }

    void Oscillator::advance(float dt) {
        d_wavePosition += dt;
    }
} // namespace audio