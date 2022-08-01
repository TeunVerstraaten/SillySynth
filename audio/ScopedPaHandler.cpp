//
// Created by pc on 13-5-22.
//

#include "ScopedPaHandler.h"

namespace audio {
    ScopedPaHandler::ScopedPaHandler() : _result(Pa_Initialize()) {
    }

    ScopedPaHandler::~ScopedPaHandler() {
        if (_result == paNoError) {
            Pa_Terminate();
        }
    }

    PaError ScopedPaHandler::result() const {
        return _result;
    }
} // namespace audio