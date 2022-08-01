//
// Created by pc on 14-5-22.
//

#include "Spectrum.h"

audio::fx::Spectrum::Spectrum() {
    in.resize(LOOK_AHEAD);
    out.resize(LOOK_AHEAD);
}

void audio::fx::Spectrum::apply(LrBuffer& lrBuffer) {
    d_plan = fftw_plan_dft_1d(LOOK_AHEAD, reinterpret_cast<fftw_complex*>(&in[0]), reinterpret_cast<fftw_complex*>(&out[0]), FFTW_FORWARD, FFTW_ESTIMATE);

    auto const& left = lrBuffer.leftBuffer;
    for (size_t i = 0; i != LOOK_AHEAD; ++i)
        in[i] = {left[i], 0};

    fftw_execute(d_plan);
    fftw_destroy_plan(d_plan);

    for (size_t i = 0; i != LOOK_AHEAD; ++i)
        d_lrBuffer.leftBuffer[i] = static_cast<float>(std::log10(std::norm(out[i])));
}

const LrBuffer& audio::fx::Spectrum::lrBuffer() const {
    return d_lrBuffer;
}
