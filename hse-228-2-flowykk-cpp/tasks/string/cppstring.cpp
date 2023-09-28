#include "cppstring.h"

#include "cstring"

String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

String::String(size_t size, char symbol) : size_(size), capacity_(size * 2) {
    if (size == 0) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = symbol;
        }
    }
}

String::String(const char *src) : size_(strlen(src)), capacity_(size_ * 2) {
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::String(const char *src, size_t size) : size_(size), capacity_(size_ * 2) {
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}

String::~String() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
}

String::String(const String &other) {
    if (other.Empty()) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    }
}

String &String::operator=(const String &other) {
    String::~String();
    if (other.Empty()) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    }
    return *this;
}

const char &String::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return *(data_ + idx);
}

char &String::operator[](size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return *(data_ + idx);
}

const char &String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return (*this)[idx];
}

char &String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return (*this)[idx];
}

const char &String::Front() const {
    if (Empty()) {
        throw StringOutOfRange();
    }
    return (*this)[0];
}

char &String::Front() {
    if (Empty()) {
        throw StringOutOfRange();
    }
    return (*this)[0];
}

const char &String::Back() const {
    if (Empty()) {
        throw StringOutOfRange();
    }
    return (*this)[size_ - 1];
}

char &String::Back() {
    if (Empty()) {
        throw StringOutOfRange();
    }
    return (*this)[size_ - 1];
}

const char *String::Data() const {
    return data_;
}

char *String::Data() {
    return data_;
}

const char *String::CStr() const {
    return data_;
}

char *String::CStr() {
    return data_;
}

bool String::Empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

size_t String::Size() const {
    return size_;
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    size_ = 0;
}

void String::Swap(String &other) {
    auto buf_size = other.size_;
    auto buf_capacity = other.capacity_;
    auto buf_data = other.data_;
    other.size_ = size_;
    other.capacity_ = capacity_;
    other.data_ = data_;
    size_ = buf_size;
    capacity_ = buf_capacity;
    data_ = buf_data;
}

void String::PopBack() {
    if (Empty()) {
        throw StringOutOfRange();
    }
    size_ -= 1;
}

void String::PushBack(char c) {
    if (capacity_ == 0) {
        capacity_ = 1;
    }
    if (size_ + 1 < capacity_) {
        data_[size_] = c;
        size_++;
    } else {
        capacity_ *= 2;
        auto buf_data = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            buf_data[i] = data_[i];
        }
        buf_data[size_] = c;
        size_++;
        delete[] data_;
        data_ = buf_data;
    }
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
            PushBack(symbol);
        }
    }
    size_ = new_size;
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        capacity_ = new_capacity;
        auto buf_data = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            buf_data[i] = data_[i];
        }
        delete[] data_;
        data_ = buf_data;
    }
}

void String::ShrinkToFit() {
    capacity_ = size_;
    auto buf_data = new char[size_];
    for (size_t i = 0; i < size_; ++i) {
        buf_data[i] = data_[i];
    }
    delete[] data_;
    data_ = buf_data;
}

int String::Compare(const String &other) const {
    for (size_t i = 0; i < std::min(other.size_, size_); ++i) {
        if (data_[i] < other[i]) {
            return -1;
        } else if (data_[i] > other[i]) {
            return 1;
        }
    }
    if (size_ < other.size_) {
        return -1;
    } else if (size_ > other.size_) {
        return 1;
    } else {
        return 0;
    }
}

String &String::operator+=(const String &other) {
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other[i]);
    }
    return *this;
}

String operator+(const String &first, const String &second) {
    auto result = first;
    return result += second;
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}

bool operator==(const String &first, const String &second) {
    return first.Compare(second) == 0;
}

bool operator!=(const String &first, const String &second) {
    return !(first == second);
}

bool operator>(const String &first, const String &second) {
    return first.Compare(second) == 1;
}

bool operator<(const String &first, const String &second) {
    return first.Compare(second) == -1;
}

bool operator>=(const String &first, const String &second) {
    return !(first < second);
}

bool operator<=(const String &first, const String &second) {
    return !(first > second);
}

void SafeCpy(char *dest, const char *src, size_t len) {
    auto result = String(src, len);
    dest = result.Data();
}
