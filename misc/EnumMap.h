//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_ENUMMAP_H
#define SYNTH_ENUMMAP_H

#include <map>
#include <string>

template <typename ENUM>
struct EnumMap {
    static const std::map<ENUM, std::string> stringMap;
};

#endif // SYNTH_ENUMMAP_H
