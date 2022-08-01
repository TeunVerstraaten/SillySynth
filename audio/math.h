//
// Created by pc on 13-5-22.
//

#ifndef SYNTH_MATH_H
#define SYNTH_MATH_H

namespace audio::math {

    template <typename Type>
    int sign(Type value) {
        return value < 0 ? -1 : 1;
    }

} // namespace audio::math

#endif // SYNTH_MATH_H
