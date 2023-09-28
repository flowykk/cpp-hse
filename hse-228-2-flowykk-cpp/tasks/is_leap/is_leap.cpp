#include "is_leap.h"

bool IsLeap(int year) {
    int const hrd = 100;
    int const fhrd = 400;
    if (year % 4 != 0 || (year % hrd == 0 && year % fhrd != 0)) {
        return false;
    }
    return true;
};
