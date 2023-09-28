#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t old_numerator1 = numerator;
    int64_t old_denumerator = denominator;
    while (numerator != denominator) {
        if (numerator > denominator) {
            numerator = numerator - denominator;
        } else {
            denominator = denominator - numerator;
        }
    }
    return old_numerator1 / numerator + old_denumerator / numerator;
}
