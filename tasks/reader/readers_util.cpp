#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) {
    reader_ = std::move(reader);
    limit_ = limit;
}

size_t LimitReader::Read(char *buf, size_t len) {
    size_t res = reader_->Read(buf, std::min(len, limit_));
    limit_ = 0;
    return res;
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : current_(0), readers_(std::move(readers)) {
}

size_t TeeReader::Read(char *buf, size_t len) {
    size_t counter = 0;
    while (counter < len && current_ < readers_.size()) {
        counter += readers_[current_]->Read(buf + counter, len - counter);
        if (counter < len) {
            ++current_;
        }
    }
    return counter;
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}

size_t HexDecodingReader::Read(char *buf, size_t len) {
    char a[2];
    size_t counter = 0;

    while (counter < len) {
        size_t res = reader_->Read(a, 2);
        if (res == 0) {
            break;
        }
        counter += 1;
        std::string s;
        s += a[0];
        s += a[1];
        const int base = 16;
        *(buf++) = static_cast<char>(std::stoi(s, 0, base));
    }
    return counter;
}
