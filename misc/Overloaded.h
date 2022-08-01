//
// Created by pc on 14-5-22.
//

#ifndef SYNTH_OVERLOADED_H
#define SYNTH_OVERLOADED_H

// https://en.cppreference.com/w/cpp/utility/variant/visit

template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

// explicit deduction guide (not needed as of C++20)
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

#endif // SYNTH_OVERLOADED_H
