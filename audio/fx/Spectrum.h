//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_SPECTRUM_H
#define SYNTH_SPECTRUM_H

#include "../../third_party/fftw-3.3.10/api/fftw3.h"
#include "../LrBuffer.h"

#include <complex>
#include <vector>

namespace audio::fx {

    class Spectrum {

      public:
        Spectrum();
        void apply(LrBuffer& lrBuffer);

        [[nodiscard]] const LrBuffer& lrBuffer() const;

      private:
        LrBuffer                          d_lrBuffer{};
        std::vector<std::complex<double>> in{};
        std::vector<std::complex<double>> out{};
        fftw_plan                         d_plan = nullptr;
    };

} // namespace audio::fx

#endif // SYNTH_SPECTRUM_H
