#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t a = 0;
    int64_t b = 1;
    int64_t c = 0;

    for (int i = 1; i < n + 1; ++i) {
        c = a + b;
        b = a;
        a = c;
    }

    return a;
}
