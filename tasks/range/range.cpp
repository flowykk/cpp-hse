#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> vect;
    if (from == to || (from < to && step <= 0) || (from > to && step >= 0)) {
        return vect;
    }
    if (from < to) {
        for (int i = from; i < to; i += step) {
            vect.push_back(i);
        }
    } else {
        for (int i = from; i > to; i += step) {
            vect.push_back(i);
        }
    }
    return vect;
}