#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int min_length = 8;
    const int max_length = 14;
    if (size(password) < min_length || size(password) > max_length) {
        return false;
    }

    bool flag = false;
    int flag_b = 0;
    int flag_s = 0;
    int flag_o = 0;
    int flag_d = 0;
    const int min_ascii = 33;
    const int max_ascii = 126;
    const int min_ascii_b = 65;
    const int max_ascii_b = 90;
    const int min_ascii_s = 97;
    const int max_ascii_s = 122;
    const int min_ascii_d = 48;
    const int max_ascii_d = 57;
    for (int i = 0; i < size(password); ++i) {
        if (static_cast<int>(password[i]) < min_ascii || static_cast<int>(password[i]) > max_ascii) {
            flag = true;
        }
        if (static_cast<int>(password[i]) >= min_ascii_b && static_cast<int>(password[i]) <= max_ascii_b) {
            flag_b = 1;
        } else if (static_cast<int>(password[i]) >= min_ascii_s && static_cast<int>(password[i]) <= max_ascii_s) {
            flag_s = 1;
        } else if (static_cast<int>(password[i]) >= min_ascii_d && static_cast<int>(password[i]) <= max_ascii_d) {
            flag_d = 1;
        } else {
            flag_o = 1;
        }
    }

    if ((flag_b + flag_s + flag_d + flag_o < 3) || flag) {
        return false;
    }

    return true;
}
