#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() {
        ptr_ = nullptr;
    }

    explicit UniquePtr(T* other) {
        ptr_ = other;
    }

    UniquePtr(const UniquePtr& other) {
        ptr_ = other.ptr_;
    }

    UniquePtr(UniquePtr&& other) {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    ~UniquePtr() {
        delete ptr_;
        ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    UniquePtr& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    void Reset() {
        delete ptr_;
        ptr_ = nullptr;
    }

    void Reset(T* obj) {
        delete ptr_;
        ptr_ = obj;
    }

private:
    T* ptr_;
};