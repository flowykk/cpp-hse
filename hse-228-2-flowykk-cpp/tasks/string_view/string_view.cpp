#include "string_view.h"

#include "cstring"
#include "iostream"

StringView::StringView() {
    string_ = nullptr;
    size_ = 0;
}

StringView::StringView(const char *source) : string_(source), size_(strlen(source)) {
}

StringView::StringView(const char *cstyle, size_t length) : string_(cstyle), size_(length) {
}

char StringView::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringViewOutOfRange();
    }
    return *(string_ + idx);
}

char StringView::At(size_t idx) const {
    if (idx >= size_) {
        throw StringViewOutOfRange();
    }
    return (*this)[idx];
}

char StringView::Front() const {
    return (*this)[0];
}

char StringView::Back() const {
    return (*this)[size_ - 1];
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

const char *StringView::Data() const {
    return string_;
}

bool StringView::Empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

void StringView::Swap(StringView &other) {
    auto buf_size = other.size_;
    auto buf_string = other.string_;
    other.size_ = size_;
    other.string_ = string_;
    size_ = buf_size;
    string_ = buf_string;
}

void StringView::RemovePrefix(size_t prefix_size) {
    size_ -= prefix_size;
    string_ += prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
    return StringView(string_ + pos, count);
}