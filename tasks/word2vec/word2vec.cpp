#include "word2vec.h"

#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> mults;
    int max = 0;
    for (int i = 1; i < vectors.size(); ++i) {
        int pr = 0;
        for (int j = 0; j < vectors[i].size(); ++j) {
            pr += vectors[i][j] * vectors[0][j];
        }
        if (i == 1) {
            max = pr;
        }
        if (pr >= max) {
            if (pr > max) {
                max = pr;
                mults.clear();
            }
            mults.push_back(words[i]);
        }
    }
    return mults;
}
