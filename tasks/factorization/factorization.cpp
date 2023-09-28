#include "factorization.h"

int Find(const std::vector<std::pair<int64_t, int>>& vector, const std::pair<int64_t, int>& pair) {
    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i].first == pair.first && vector[i].second == pair.second) {
            return i;
        }
    }
    return -1;
}

int Count(const std::vector<int64_t>& vector, const int64_t& number) {
    int count = 0;
    for (int64_t i : vector) {
        if (i == number) {
            count++;
        }
    }
    return count;
}

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<int64_t> factors;
    for (int64_t i = 2; i * i <= x; i++) {
        while (x % i == 0) {
            factors.push_back(i);
            x /= i;
        }
    }

    if (x != 1) {
        factors.push_back(x);
    }

    std::vector<std::pair<int64_t, int>> answer;
    for (int i = 0; i < factors.size(); ++i) {
        std::pair<int64_t, int> pair{factors[i], Count(factors, factors[i])};
        if (Find(answer, pair) == -1) {
            answer.push_back(pair);
        }
    }

    return answer;
}