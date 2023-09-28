#pragma once
#include <iostream>

#include "cmath"
template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

class RangeIterator {
public:
    RangeIterator() : from_(0), step_(1) {
    }

    explicit RangeIterator(int64_t from) : from_(from), step_(1) {
    }

    RangeIterator(int64_t from, int64_t step) : from_(from), step_(step) {
    }

    const auto operator*() const {
        return from_;
    }

    RangeIterator operator++() {
        from_ += step_;
        return *this;
    }

    const bool operator!=(const RangeIterator& other) const {
        return from_ != other.from_;
    }

private:
    int64_t from_;
    int64_t step_;
};

inline const IteratorRange<RangeIterator> Range(int64_t to) {
    auto begin = RangeIterator(0);
    auto end = RangeIterator(to);
    return IteratorRange<RangeIterator>(begin, end);
}

inline const IteratorRange<RangeIterator> Range(int64_t from, int64_t to, int64_t step = 1) {
    auto begin = RangeIterator(from, step);
    auto end = RangeIterator(
        from + (static_cast<int64_t>(std::ceil(static_cast<double>(to - from) / static_cast<double>(step)))) * step,
        step);
    return IteratorRange<RangeIterator>(begin, end);
}

template <typename T, typename U>
class ZipIterator {
public:
    ZipIterator(T first, U second) : curr_first_(first), curr_second_(second) {
    }

    const auto operator*() const {
        return std::make_pair(*curr_first_, *curr_second_);
    }

    ZipIterator operator++() {
        ++curr_first_;
        ++curr_second_;
        return *this;
    }

    const bool operator!=(const ZipIterator& other) const {
        return curr_first_ != other.curr_first_;
    }

private:
    T curr_first_;
    U curr_second_;
};

template <typename T, typename U>
const auto Zip(const T& first, const U& second) {
    auto begin = ZipIterator<decltype(first.begin()), decltype(second.begin())>(first.begin(), second.begin());
    auto b1 = first.begin();
    auto b2 = second.begin();
    while (b1 != first.end() && b2 != second.end()) {
        ++b1;
        ++b2;
    }
    auto end = ZipIterator<decltype(first.begin()), decltype(second.begin())>(b1, b2);
    return IteratorRange<ZipIterator<decltype(first.begin()), decltype(second.begin())>>(begin, end);
}

template <typename T>
class GroupIterator {
public:
    explicit GroupIterator(T begin, T end) : begin_(begin), end_(end) {
    }

    const auto operator*() {
        T begin = begin_;
        T end = begin_;
        while (end != end_ && *begin == *end) {
            ++end;
        }
        return IteratorRange<T>(begin, end);
    }

    GroupIterator operator++() {
        T curr = begin_;
        while (begin_ != end_ && *curr == *begin_) {
            ++begin_;
        }
        return *this;
    }

    const bool operator!=(const GroupIterator& other) const {
        return begin_ != other.begin_;
    }

private:
    T begin_;
    T end_;
};

template <typename T>
const auto Group(const T& first) {
    auto begin = GroupIterator<decltype(first.begin())>(first.begin(), first.end());
    auto end = GroupIterator<decltype(first.begin())>(first.end(), first.end());
    return IteratorRange<GroupIterator<decltype(first.begin())>>(begin, end);
}