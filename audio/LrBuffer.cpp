//
// Created by pc on 13-5-22.
//

#include "LrBuffer.h"

size_t LrBuffer::size() {
    return LOOK_AHEAD;
}

void LrBuffer::setToZero() {
    leftBuffer  = {};
    rightBuffer = {};
}
