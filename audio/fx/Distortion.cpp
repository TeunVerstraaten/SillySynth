//
// Created by pc on 14-5-22.
//

#include "Distortion.h"

#include <cmath>

static float power_distortion(float x, float amount) {
    if (x > 0)
        return std::pow(x, amount);
    else
        return -std::pow(-x, amount);
}

static float exponential_distortion(float x, float amount) {
    if (amount < 0.01)
        amount = 0.01;
    float const normalizer = 1.0f - std::exp(-1.0f / amount);
    if (x > 0)
        return (1.0f - std::exp(-x / amount)) / normalizer;
    else
        return (-1.0f + std::exp(x / amount)) / normalizer;
}

namespace audio::fx {
    Distortion::Distortion(Distortion::TYPE type, float amount) : d_type(type), d_amount(amount) {
    }

    void Distortion::apply(LrBuffer& lrBuffer) {
        float const distCoefficient = 1.0f - d_amount;
        switch (d_type) {
            case TYPE::POWER:
                for (size_t i = 0; i != LrBuffer::size(); ++i) {
                    lrBuffer.leftBuffer[i]  = power_distortion(lrBuffer.leftBuffer[i], distCoefficient);
                    lrBuffer.rightBuffer[i] = power_distortion(lrBuffer.rightBuffer[i], distCoefficient);
                }
                break;
            case TYPE::EXP:
                for (size_t i = 0; i != LrBuffer::size(); ++i) {
                    lrBuffer.leftBuffer[i]  = exponential_distortion(lrBuffer.leftBuffer[i], distCoefficient);
                    lrBuffer.rightBuffer[i] = exponential_distortion(lrBuffer.rightBuffer[i], distCoefficient);
                }
                break;
        }
    }

    Distortion::TYPE& Distortion::type() {
        return d_type;
    }

    float& Distortion::amount() {
        return d_amount;
    }

} // namespace audio::fx