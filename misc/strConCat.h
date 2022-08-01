//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_STRCONCAT_H
#define SYNTH_STRCONCAT_H

#include <sstream>
#include <string>

template <typename... Ts>
std::string strConCat(Ts const&... ts) {
    std::stringstream s;
    (s << ... << ts);
    return s.str();
}

#endif // SYNTH_STRCONCAT_H
