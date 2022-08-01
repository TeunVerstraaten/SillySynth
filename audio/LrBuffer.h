//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_LRBUFFER_H
#define SYNTH_LRBUFFER_H

#include "Defines.h"

#include <array>
#include <cstddef>

struct LrBuffer {

    std::array<float, LOOK_AHEAD> leftBuffer;
    std::array<float, LOOK_AHEAD> rightBuffer;

    [[nodiscard]] static size_t size();

    void setToZero();
};

#endif // SYNTH_LRBUFFER_H
