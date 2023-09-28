#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    int64_t sum = 0;
    int64_t const ten = 10;
    while (number) {
        sum += number % ten;
        number /= ten;
    }
    return sum;
}