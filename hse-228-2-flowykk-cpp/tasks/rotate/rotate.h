#pragma once
#include <string>

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    if (begin != end) {
        for (auto i = begin; i < --end; ++i) {
            std::swap(*i, *end);
        }
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    if (begin == mid) {
        return;
    }

    if (mid == end) {
        return;
    }

    auto swapped = begin;
    auto begin_tracker = begin;
    for (auto i = mid; i < end; ++i) {
        if (swapped == begin_tracker) {
            begin_tracker = i;
        }
        std::swap(*swapped, *i);
        ++swapped;
    }

    Rotate(swapped, begin_tracker, end);
}
