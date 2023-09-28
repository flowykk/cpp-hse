#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string result;
    for (int i = 0; i < cipher.size(); ++i) {
        if (cipher[i] - shift < static_cast<int>('A')) {
            size_t delta = shift - (static_cast<int>(cipher[i]) - static_cast<int>('A')) - 1;
            result += static_cast<char>(static_cast<int>('Z') - delta);
        } else {
            result += static_cast<char>(cipher[i] - shift);
        }
    }
    return result;
}
