#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <type_traits>
#include <cassert>

namespace muser::util {
    std::string random_template_file();
    template <typename T, bool check = std::is_arithmetic<T>::value>
    T constrain(T val, T lower_bound, T upper_bound) {
        assert(check);
        if (val > upper_bound) return upper_bound;
        else if (val < lower_bound) return lower_bound;
        return val;
    }
}  // namespace muser::util

#endif