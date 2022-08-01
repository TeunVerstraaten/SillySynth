//
// Created by pc on 13-5-22.
//

#include "Bus.h"

#include <cstddef>

namespace audio {
    void Bus::add(const LrBuffer& buffer, float mutliplier) {
        if (mutliplier == 0.0f)
            return;
        for (size_t i = 0; i != LOOK_AHEAD; ++i)
            d_lrBuffer.leftBuffer[i] += mutliplier * buffer.leftBuffer[i];

        for (size_t i = 0; i != LOOK_AHEAD; ++i)
            d_lrBuffer.rightBuffer[i] += mutliplier * buffer.rightBuffer[i];
    }

    void Bus::reset() {
        d_lrBuffer.setToZero();
    }

    void Bus::process() {
        for (auto& effect : d_effects)
            effect.apply(d_lrBuffer);
    }

    const LrBuffer& Bus::lrBuffer() const {
        return d_lrBuffer;
    }

    std::array<fx::Effect, NUM_EFFECTS_PER_BUS>& Bus::effects() {
        return d_effects;
    }
} // namespace audio
