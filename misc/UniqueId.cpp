//
// Created by pc on 14-5-22.
//

#include "UniqueId.h"

UniqueId::UniqueId() : d_id(s_max) {
    ++s_max;
}

size_t UniqueId::id() const {
    return d_id;
}
