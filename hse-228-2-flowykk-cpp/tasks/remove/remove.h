#pragma once
#include "iostream"

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T b = begin;
    int count_values = 0;
    int count_els = 0;
    for (auto i = begin; i < end; ++i) {
        ++count_els;
        if (*i == value) {
            ++count_values;
        } else if (count_values != 0 && *i != value) {
            std::swap(*i, *(i - count_values));
        }
    }
    return b + count_els - count_values;
}
