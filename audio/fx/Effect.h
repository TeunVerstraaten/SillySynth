//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_EFFECT_H
#define SYNTH_EFFECT_H

#include "../../misc/UniqueId.h"
#include "Distortion.h"
#include "Empty.h"
#include "Spectrum.h"

#include <string>
#include <variant>

namespace audio::fx {

    class Effect : public UniqueId {

      public:
        typedef std::variant<Empty, Distortion, Spectrum> EffectVariant;

        Effect() = default;
        explicit Effect(EffectVariant&& effectVariant);

        void                         apply(LrBuffer& effect);
        [[nodiscard]] bool           empty() const;
        [[nodiscard]] bool           bypass() const;
        [[nodiscard]] std::string    getName() const;
        [[nodiscard]] EffectVariant& effectVariant();

      private:
        bool          d_bypass        = false;
        EffectVariant d_effectVariant = Empty{};
    };

} // namespace audio::fx

#endif // SYNTH_EFFECT_H
