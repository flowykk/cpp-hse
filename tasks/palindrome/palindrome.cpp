#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t start_symb = str.size() - 1;
    size_t end_symb = 0;
    while (end_symb < start_symb) {
        if (str[end_symb] == ' ') {
            end_symb++;
        } else if (str[start_symb] == ' ') {
            start_symb--;
        } else {
            if (str[end_symb] != str[start_symb]) {
                return false;
            }
            end_symb++;
            start_symb--;
        }
    }
    return true;
}