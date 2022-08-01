//
// Created by pc on 13-5-22.
//

#include "EnumMap.h"

#include "../audio/Oscillator.h"
#include "../audio/fx/Distortion.h"

template <>
struct EnumMap<audio::Oscillator::OSC_TYPE> {
    static const std::map<audio::Oscillator::OSC_TYPE, std::string> stringMap;
};

const std::map<audio::Oscillator::OSC_TYPE, std::string> EnumMap<audio::Oscillator::OSC_TYPE>::stringMap = {
    {audio::Oscillator::SINE, "Sine"}, {audio::Oscillator::SAW, "Saw"}, {audio::Oscillator::TRIANGLE, "Tri"}, {audio::Oscillator::SQUARE, "Sqr"}};

template <>
struct EnumMap<audio::fx::Distortion::TYPE> {
    static const std::map<audio::fx::Distortion::TYPE, std::string> stringMap;
};

const std::map<audio::fx::Distortion::TYPE, std::string> EnumMap<audio::fx::Distortion::TYPE>::stringMap = {{audio::fx::Distortion::TYPE::POWER, "Power"},
                                                                                                            {audio::fx::Distortion::TYPE::EXP, "Exp"}};