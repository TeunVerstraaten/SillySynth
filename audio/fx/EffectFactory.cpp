//
// Created by pc on 14-5-22.
//

#include "EffectFactory.h"

#include "../../misc/EnumMap.h"

template <>
struct EnumMap<audio::fx::EffectFactory::EFFECT_ENUM> {
    static const std::map<audio::fx::EffectFactory::EFFECT_ENUM, std::string> stringMap;
};

const std::map<audio::fx::EffectFactory::EFFECT_ENUM, std::string> EnumMap<audio::fx::EffectFactory::EFFECT_ENUM>::stringMap = {
    {audio::fx::EffectFactory::EFFECT_ENUM::EMPTY, "Empty"},
    {audio::fx::EffectFactory::EFFECT_ENUM::DISTORTION, "Distortion"},
    {audio::fx::EffectFactory::EFFECT_ENUM::SPECTRUM, "Spectrum"}};

namespace audio::fx {

    Effect EffectFactory::build(audio::fx::EffectFactory::EFFECT_ENUM anEnum) {
        switch (anEnum) {
            case EFFECT_ENUM::EMPTY:
                return Effect{Empty{}};
            case EFFECT_ENUM::DISTORTION:
                return Effect{Distortion{Distortion::TYPE::POWER, 0.5f}};
            case EFFECT_ENUM::SPECTRUM:
                return Effect{Spectrum{}};
        }
        return Effect{Empty{}};
    }

} // namespace audio::fx