#include "cstring.h"

#include "iostream"

size_t Strlen(const char *str) {
    size_t result = 0;
    while (*str != 0) {
        ++result;
        ++str;
    }
    return result;
}

int Strcmp(const char *first, const char *second) {
    for (int i = 0; i < std::min(Strlen(first), Strlen(second)); ++i) {
        if (first[i] > second[i]) {
            return 1;
        } else if (first[i] < second[i]) {
            return -1;
        }
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    } else if (Strlen(first) < Strlen(second)) {
        return -1;
    } else {
        return 0;
    }
}

int Strncmp(const char *first, const char *second, size_t count) {
    if (count == 0) {
        return 0;
    }
    size_t i = 0;
    for (i = 0; i < std::min(std::min(Strlen(first), Strlen(second)), count); ++i) {
        if (first[i] > second[i]) {
            return 1;
        } else if (first[i] < second[i]) {
            return -1;
        }
    }
    if (i == count) {
        return 0;
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    } else if (Strlen(first) < Strlen(second)) {
        return -1;
    } else {
        return 0;
    }
}

char *Strcpy(char *dest, const char *src) {
    auto len = Strlen(src);
    if (dest < src || dest > src + len) {
        for (size_t i = 0; i <= len; ++i) {
            dest[i] = src[i];
        }
    }
    return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
    auto len = Strlen(src);
    if (dest < src || dest > src + len) {
        for (size_t i = 0; i < count; ++i) {
            if (i > len) {
                dest[i] = 0;
            } else {
                dest[i] = src[i];
            }
        }
    }
    dest[Strlen(dest)] = 0;
    return dest;
}

char *Strcat(char *dest, const char *src) {
    auto len = Strlen(dest);
    for (size_t i = 0; i < Strlen(src); ++i) {
        dest[i + len] = src[i];
    }
    return dest;
}

char *Strncat(char *dest, const char *src, size_t count) {
    auto len = Strlen(dest);
    if (count > Strlen(src)) {
        return Strcat(dest, src);
    }
    size_t i = 0;
    for (i = 0; i < count; ++i) {
        dest[i + len] = src[i];
    }
    dest[len + i] = 0;
    return dest;
}

const char *Strchr(const char *str, char symbol) {
    if (symbol == 0) {
        return &str[Strlen(str)];
    }
    while (*str != 0) {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }
    return nullptr;
}

const char *Strrchr(const char *str, char symbol) {
    if (symbol == 0) {
        return &str[Strlen(str)];
    }
    const char *result = nullptr;
    while (*str != 0) {
        if (*str == symbol) {
            result = str;
        }
        ++str;
    }
    return result;
}

size_t Strspn(const char *dest, const char *src) {
    size_t i = 0;
    for (i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) == nullptr) {
            return i;
        }
    }
    return i;
}

size_t Strcspn(const char *dest, const char *src) {
    size_t i = 0;
    for (i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) != nullptr) {
            return i;
        }
    }
    return i;
}

const char *Strpbrk(const char *dest, const char *breakset) {
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(breakset, dest[i]) != nullptr) {
            return dest + i;
        }
    }
    return nullptr;
}

const char *Strstr(const char *str, const char *pattern) {
    if (*pattern == 0) {
        return str;
    }
    while (*str != 0) {
        const char *ptr = pattern;
        const char *ptr_str = str;
        while (*ptr != 0 && *ptr_str != 0 && *ptr_str == *ptr) {
            ++ptr_str;
            ++ptr;
        }
        if (*ptr == 0) {
            return str;
        }
        ++str;
    }
    return nullptr;
}
