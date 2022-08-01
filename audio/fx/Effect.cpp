//
// Created by pc on 14-5-22.
//

#include "Effect.h"

#include "../../misc/Overloaded.h"

namespace audio::fx {

    Effect::Effect(EffectVariant&& effectVariant) : d_effectVariant(effectVariant) {
    }

    std::string Effect::getName() const {
        return std::visit(Overloaded{[](Distortion const&) { return "dstr"; }, [](Spectrum const&) { return "spec"; }, [](Empty const&) { return "."; }}, d_effectVariant);
    }

    void Effect::apply(LrBuffer& lrBuffer) {
        std::visit(Overloaded{[&](auto& effect) { effect.apply(lrBuffer); }, [](Empty&) {}}, d_effectVariant);
    }

    bool Effect::empty() const {
        return std::holds_alternative<Empty>(d_effectVariant);
    }

    Effect::EffectVariant& Effect::effectVariant() {
        return d_effectVariant;
    }

    bool Effect::bypass() const {
        return d_bypass;
    }

} // namespace audio::fx