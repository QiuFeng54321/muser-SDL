#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdio.h>
#include <stdlib.h>

#include <cassert>
#include <string>
#include <type_traits>
#include <vector>
#include <sstream>

namespace muser::util {
    std::string random_template_file();
    template <typename T, bool check = std::is_arithmetic<T>::value>
    inline T constrain(T val, T lower_bound, T upper_bound) {
        static_assert(check);
        if (val > upper_bound)
            return upper_bound;
        else if (val < lower_bound)
            return lower_bound;
        return val;
    }
    inline std::vector<std::string> Split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    inline bool has_only_digits(const std::string& s) {
        return s.find_first_not_of("0123456789") == std::string::npos;
    }
    //https://stackoverflow.com/a/29634934/11225486
    namespace detail {
        // To allow ADL with custom begin/end
        using std::begin;
        using std::end;

        template <typename T>
        auto is_iterable_impl(int)
            -> decltype(
                begin(std::declval<T&>()) != end(std::declval<T&>()),    // begin/end and operator !=
                void(),                                                  // Handle evil operator ,
                ++std::declval<decltype(begin(std::declval<T&>()))&>(),  // operator ++
                void(*begin(std::declval<T&>())),                        // operator*
                std::true_type{});

        template <typename T>
        std::false_type is_iterable_impl(...);

    }  // namespace detail

    template <typename T>
    using is_iterable = decltype(detail::is_iterable_impl<T>(0));
}  // namespace muser::util

#endif