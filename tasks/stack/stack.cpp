#include "stack.h"

Node::Node(int32_t value, Node* previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    size_ = 0;
    head_ = new Node(0, 0);
}

Stack::~Stack() {
    while (head_->previous != 0) {
        Node* new_head = head_->previous;
        delete (head_);
        head_ = new_head;
    }
    delete (head_);
}

void Stack::Push(int32_t value) {
    ++size_;
    head_ = new Node(value, head_);
}

void Stack::Pop() {
    if (size_ != 0 && head_->previous != 0) {
        --size_;
        Node* new_head = head_->previous;
        delete (head_);
        head_ = new_head;
    }
}

int32_t Stack::Top() const {
    if (size_ != 0 && head_->value != 0 && head_->previous != 0) {
        return head_->value;
    }
    return 0;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    Stack::~Stack();
}

bool Stack::Empty() const {
    return Size() == 0;
}
