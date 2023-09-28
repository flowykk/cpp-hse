#pragma once
#include "iostream"
#include "iterator"

template <class T>
class Vector {
public:
    Vector() {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    explicit Vector(size_t size) {
        size_ = size;
        capacity_ = size_ * 2;
        if (size == 0) {
            data_ = nullptr;
        }
        data_ = new int[capacity_];
        std::fill(data_, data_ + size_, 0);
    }

    Vector(std::initializer_list<int> list) {
        size_ = list.size();
        capacity_ = size_;
        data_ = new int[capacity_];
        int* buf = data_;
        for (auto i = list.begin(); i != list.end(); ++i) {
            *(buf++) = *i;
        }
    }

    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(Vector&& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] data_;
        data_ = new int[capacity_];
        for (int i = 0; i < size_; ++i) {
            *(data_ + i) = *(other.data_ + i);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            delete[] data_;
            data_ = other.data_;
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~Vector() {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    void Swap(Vector& other) {
        auto buf_size = size_;
        auto buf_capacity = capacity_;
        auto buf_data = data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.size_ = buf_size;
        other.capacity_ = buf_capacity;
        other.data_ = buf_data;
    }

    int& operator[](size_t idx) {
        return data_[idx];
    }

    const int& operator[](size_t idx) const {
        return data_[idx];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int el) {
        if (size_ < capacity_) {
            data_[size_] = el;
            size_++;
        } else {
            if (capacity_ == 0) {
                capacity_ = 1;
            }
            capacity_ *= 2;
            auto buf_data = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                buf_data[i] = data_[i];
            }
            buf_data[size_] = el;
            size_++;
            delete[] data_;
            data_ = buf_data;
        }
    }

    void PopBack() {
        size_ -= 1;
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            capacity_ = new_capacity;
            auto buf_data = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                buf_data[i] = data_[i];
            }
            delete[] data_;
            data_ = buf_data;
        }
    }

    class Iterator : public std::iterator<std::random_access_iterator_tag, int, int, int*, int> {
    public:
        Iterator() {
            ptr_ = nullptr;
        }

        explicit Iterator(int* n) {
            ptr_ = n;
        }

        Iterator(const Iterator& other) {
            ptr_ = other.ptr_;
        }

        Iterator(Iterator&& other) {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }

        Iterator& operator=(Iterator&& other) {
            if (this != &other) {
                delete ptr_;
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }

        Iterator& operator++() {
            ptr_ += 1;
            return *this;
        }

        Iterator& operator--() {
            ptr_ -= 1;
            return *this;
        }

        Iterator operator++(int) {
            Iterator buf = *this;
            ++(*this);
            return buf;
        }

        Iterator operator--(int) {
            Iterator buf = *this;
            --(*this);
            return buf;
        }

        Iterator& operator+=(int n) {
            ptr_ += n;
            return *this;
        }

        Iterator& operator-=(int n) {
            ptr_ += -n;
            return *this;
        }

        Iterator operator+(int n) {
            return Iterator(ptr_ + n);
        }

        Iterator operator-(int n) {
            return Iterator(ptr_ - n);
        }

        int operator-(Iterator& other) {
            return ptr_ - other.ptr_;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

        int& operator*() {
            return *ptr_;
        }

        int* operator->() {
            return ptr_;
        }

    private:
        int* ptr_;
    };

    Iterator Begin() {
        return Iterator(data_);
    }

    Iterator begin() {  // NOLINT
        return Iterator(data_);
    }

    Iterator End() {
        return Iterator(data_ + size_);
    }

    Iterator end() {  // NOLINT
        return Iterator(data_ + size_);
    }

private:
    size_t size_;
    size_t capacity_;
    int* data_;
};