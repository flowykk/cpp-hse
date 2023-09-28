#pragma once
#include <memory>

#include "iostream"

struct BaseNode {
public:
    BaseNode() {
        next_ = nullptr;
        prev_ = nullptr;
    }

    BaseNode(BaseNode* next, BaseNode* prev) {
        next_ = next;
        prev_ = prev;
    }

    virtual ~BaseNode() {
    }

    BaseNode* next_;
    BaseNode* prev_;
};

template <typename T>
struct Node : BaseNode {
public:
    Node(std::unique_ptr<T>&& value, BaseNode* next, BaseNode* prev) {
        value_ = std::move(value);
        next_ = next;
        prev_ = prev;
    }

    auto GetValue() {
        return std::ref(*value_);
    }

    ~Node() override {
        value_.reset();
    }

    std::unique_ptr<T> value_;
};

template <typename T>
class List {
private:
    BaseNode* front_;
    BaseNode* tail_;
    size_t size_;

public:
    class Iterator {
    public:
        explicit Iterator(BaseNode* ptr, BaseNode* begin, bool flag) {
            flag_ = flag;
            begin_ = begin;
            ptr_ = ptr;
        }

        Iterator& operator++() {
            ptr_ = ptr_->next_;
            if (ptr_ == begin_) {
                flag_ = true;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator buf = *this;
            ++(*this);
            return buf;
        }

        Iterator& operator--() {
            ptr_ = ptr_->prev_;
            flag_ = false;
            return *this;
        }

        Iterator operator--(int) {
            Iterator buf = *this;
            --(*this);
            return buf;
        }

        T& operator*() const {
            return static_cast<Node<T>*>(ptr_)->GetValue();
        }

        T* operator->() const {
            return &(static_cast<Node<T>*>(ptr_)->GetValue());
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_ && flag_ == rhs.flag_;
        }

        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_ || flag_ != rhs.flag_;
        }

        auto GetNode() {
            return ptr_;
        }

    private:
        BaseNode* ptr_;
        BaseNode* begin_;
        bool flag_;
    };

    List() {
        front_ = new BaseNode(nullptr, nullptr);
        tail_ = front_;
        front_->prev_ = tail_;
        front_->next_ = tail_;
        size_ = 0;
    }

    List(const List& list) {
        if (list.IsEmpty()) {
            front_ = new BaseNode(nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
            size_ = 0;
        } else if (list.size_ == 1) {
            front_ = new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.front_)->GetValue()), nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
            size_ = 1;
        } else {
            size_ = list.size_;
            front_ = new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.front_)->GetValue()), nullptr, nullptr);
            tail_ = new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.tail_)->GetValue()), front_, front_);
            front_->next_ = tail_;
            front_->prev_ = tail_;
            auto it_list = list.Begin();
            auto end_list = list.End();
            auto it_this = Begin();
            ++it_list;
            while (it_list != end_list) {
                LinkAfter(it_this.GetNode(), new Node<T>(std::make_unique<T>(*it_list), nullptr, nullptr));
                ++it_list;
                ++it_this;
            }
        }
    }

    List(List&& list) {
        size_ = list.size_;
        front_ = list.front_;
        tail_ = list.tail_;
        list.front_ = new BaseNode(nullptr, nullptr);
        list.tail_ = list.front_;
        list.front_->prev_ = list.tail_;
        list.front_->next_ = list.tail_;
        list.size_ = 0;
    }

    ~List() {
        while (front_->next_ != tail_) {
            Unlink(front_->next_);
        }
        if (size_ <= 1) {
            delete front_;
        } else {
            delete front_;
            front_ = nullptr;
            delete tail_;
        }
    }

    void Clear() {
        while (front_->next_ != tail_) {
            Unlink(front_->next_);
        }
        if (size_ <= 1) {
            delete front_;
        } else {
            delete front_;
            front_ = nullptr;
            delete tail_;
        }
    }

    void Unlink(BaseNode* node) {
        auto prev = node->prev_;
        auto next = node->next_;
        prev->next_ = next;
        next->prev_ = prev;
        delete node;
    }

    void LinkAfter(BaseNode* target, BaseNode* after) {
        auto target_next = target->next_;
        target->next_ = after;
        after->next_ = target_next;
        after->prev_ = target;
        target_next->prev_ = after;
    }

    List& operator=(const List& list) {
        if (this != &list) {
            Clear();
            if (list.IsEmpty()) {
                front_ = new BaseNode(nullptr, nullptr);
                tail_ = front_;
                front_->prev_ = tail_;
                front_->next_ = tail_;
                size_ = 0;
            } else if (list.size_ == 1) {
                front_ =
                    new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.front_)->GetValue()), nullptr, nullptr);
                tail_ = front_;
                front_->prev_ = tail_;
                front_->next_ = tail_;
                size_ = 1;
            } else {
                size_ = list.size_;
                front_ =
                    new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.front_)->GetValue()), nullptr, nullptr);
                tail_ = new Node<T>(std::make_unique<T>(static_cast<Node<T>*>(list.tail_)->GetValue()), front_, front_);
                front_->next_ = tail_;
                front_->prev_ = tail_;
                auto it_list = list.Begin();
                auto end_list = list.End();
                auto it_this = Begin();
                ++it_list;
                while (it_list != end_list) {
                    LinkAfter(it_this.GetNode(), new Node<T>(std::make_unique<T>(*it_list), nullptr, nullptr));
                    ++it_list;
                    ++it_this;
                }
            }
        }
        return *this;
    }

    List& operator=(List&& list) {
        if (this != &list) {
            Clear();
            size_ = list.size_;
            front_ = list.front_;
            tail_ = list.tail_;
            list.front_ = new BaseNode(nullptr, nullptr);
            list.tail_ = list.front_;
            list.front_->prev_ = list.tail_;
            list.front_->next_ = list.tail_;
            list.size_ = 0;
        }
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        if (IsEmpty()) {
            size_ = 1;
            delete front_;
            front_ = new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
        } else {
            LinkAfter(tail_, new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr));
            tail_ = tail_->next_;
            ++size_;
        }
    }

    void PushBack(T&& elem) {
        if (IsEmpty()) {
            size_ = 1;
            delete front_;
            front_ = new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
        } else {
            LinkAfter(tail_, new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr));
            tail_ = tail_->next_;
            ++size_;
        }
    }

    void PushFront(const T& elem) {
        if (IsEmpty()) {
            size_ = 1;
            delete front_;
            front_ = new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
        } else {
            LinkAfter(tail_, new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr));
            ++size_;
            front_ = front_->prev_;
        }
    }

    void PushFront(T&& elem) {
        if (IsEmpty()) {
            size_ = 1;
            delete front_;
            front_ = new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr);
            tail_ = front_;
            front_->prev_ = tail_;
            front_->next_ = tail_;
        } else {
            LinkAfter(tail_, new Node<T>(std::make_unique<T>(std::move(elem)), nullptr, nullptr));
            ++size_;
            front_ = front_->prev_;
        }
    }

    T& Front() {
        return static_cast<Node<T>*>(front_)->GetValue();
    }
    const T& Front() const {
        return static_cast<Node<T>*>(front_)->GetValue();
    }
    T& Back() {
        return static_cast<Node<T>*>(tail_)->GetValue();
    }
    const T& Back() const {
        return static_cast<Node<T>*>(tail_)->GetValue();
    }

    void PopBack() {
        if (size_ > 1) {
            tail_ = tail_->prev_;
            Unlink(tail_->next_);
            --size_;
        } else if (size_ == 1) {
            --size_;
        }
    }

    void PopFront() {
        if (size_ > 1) {
            front_ = front_->next_;
            Unlink(front_->prev_);
            --size_;
        } else if (size_ == 1) {
            --size_;
        }
    }

    Iterator Begin() const {
        return Iterator(front_, front_, false);
    }
    Iterator End() const {
        return Iterator(front_, front_, true);
    }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}
