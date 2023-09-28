#pragma once

#include <memory>
#include <string>
#include <vector>

using std::string;

template <class T>
std::shared_ptr<T> IsHereS(std::vector<std::shared_ptr<T>> out, T el) {
    for (int i = 0; i < out.size(); ++i) {
        if (*(out[i]) == el) {
            return out[i];
        }
    }
    return nullptr;
}

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> out;
    for (auto i = 0; i < items.size(); ++i) {
        out.emplace_back(std::make_unique<T>(*(items[i])));
    }
    return out;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> out;
    for (auto i = 0; i < items.size(); ++i) {
        std::shared_ptr<T> buf = std::make_shared<T>(*(items[i]));
        if (IsHereS(out, *(items[i])) == nullptr) {
            out.push_back(buf);
        } else {
            out.push_back(IsHereS(out, *(items[i])));
        }
    }
    return out;
}
