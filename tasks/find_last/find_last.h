#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator result = last;
    for (auto i = first; i < last; ++i) {
        if (*i == val) {
            result = i;
        }
    }
    return result;
}
