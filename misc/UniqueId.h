//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_UNIQUEID_H
#define SYNTH_UNIQUEID_H

#include <cstddef>

class UniqueId {

  public:
    UniqueId();

    [[nodiscard]] size_t id() const;

  private:
    size_t               d_id;
    inline static size_t s_max = 0;
};

#endif // SYNTH_UNIQUEID_H
