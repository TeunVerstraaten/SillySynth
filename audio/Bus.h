//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_BUS_H
#define SYNTH_BUS_H

#include "LrBuffer.h"
#include "fx/Effect.h"


namespace audio {

    class Bus {

    public:
        void reset();

        void process();

        void add(LrBuffer const &buffer, float mutliplier);

        [[nodiscard]] const LrBuffer &lrBuffer() const;

        std::array<fx::Effect, NUM_EFFECTS_PER_BUS> &effects();

    private:
        LrBuffer d_lrBuffer{};
        std::array<fx::Effect, NUM_EFFECTS_PER_BUS> d_effects = {};
    };

} // namespace audio

#endif // SYNTH_BUS_H
