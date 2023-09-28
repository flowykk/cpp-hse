#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    std::multiset<int64_t> set;
    for (int i = 0; i < provinces.size(); ++i) {
        set.insert(provinces[i]);
    }

    int64_t result = 0;
    while (set.size() != 1) {
        auto fst = set.begin();
        auto snd = ++set.begin();
        auto new_province = *fst + *(snd);
        result += new_province;
        set.erase(fst);
        set.erase(snd);
        set.insert(new_province);
    }

    return result;
}
