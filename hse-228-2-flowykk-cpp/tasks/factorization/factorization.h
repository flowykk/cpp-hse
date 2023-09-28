#pragma once

#include <utility>
#include <vector>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x);
int Find(const std::vector<std::pair<int64_t, int>>& vector, const std::pair<int64_t, int>& pair);
int Count(const std::vector<int64_t>& vector, const int64_t& number);