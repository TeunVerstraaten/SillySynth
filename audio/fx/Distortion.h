//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_DISTORTION_H
#define SYNTH_DISTORTION_H

#include "../LrBuffer.h"

namespace audio::fx {
    class Distortion {

      public:
        enum class TYPE { POWER, EXP };

        Distortion(TYPE type, float amount);

        TYPE&  type();
        float& amount();
        void   apply(LrBuffer& lrBuffer);

      private:
        TYPE  d_type   = TYPE::POWER;
        float d_amount = 0.5f;
    };
} // namespace audio::fx

#endif // SYNTH_DISTORTION_H
