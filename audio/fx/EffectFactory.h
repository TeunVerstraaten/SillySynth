//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_EFFECTFACTORY_H
#define SYNTH_EFFECTFACTORY_H

#include "Effect.h"

namespace audio::fx {

    class EffectFactory {

      public:
        enum class EFFECT_ENUM { EMPTY, DISTORTION, SPECTRUM };

        static Effect build(EFFECT_ENUM anEnum);
    };
} // namespace audio::fx

#endif // SYNTH_EFFECTFACTORY_H
