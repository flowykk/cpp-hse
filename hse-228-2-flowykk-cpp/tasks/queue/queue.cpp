#include "queue.h"

Node::Node(int32_t value, Node* next) {
    this->value = value;
    this->next = next;
}

Queue::Queue() {
    size_ = 0;
    tail_ = new Node(0, nullptr);
    front_ = new Node(0, nullptr);
}

Queue::~Queue() {
    while (front_->next != 0) {
        Node* new_front = front_->next;
        delete front_;
        front_ = new_front;
    }
    delete front_->next;
    delete front_;
}

void Queue::Push(int32_t value) {
    if (Empty()) {
        ++size_;
        delete front_;
        front_ = tail_;
        front_->value = value;
    } else {
        ++size_;
        Node* new_next = new Node(value, nullptr);
        tail_->next = new_next;
        tail_ = new_next;
    }
}

void Queue::Pop() {
    if (size_ == 1) {
        --size_;
    } else if (!Empty()) {
        --size_;
        Node* new_front = front_->next;
        delete front_;
        front_ = new_front;
    }
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    Queue::~Queue();
}

bool Queue::Empty() const {
    return (size_ == 0);
}
