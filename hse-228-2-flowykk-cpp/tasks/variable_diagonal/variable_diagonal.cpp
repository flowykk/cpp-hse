#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** table = new int*[lines];
    for (int i = 0; i < lines; ++i) {
        table[i] = new int[columns];
    }
    int curr_num = 0;

    for (int i = 0; i < lines; ++i) {
        int current_i = i;
        for (int j = 0; j < i + 1; ++j) {
            int current_j = j;
            table[current_j--][current_i--] = curr_num++;
        }
    }

    for (int i = 1; i < lines; ++i) {
        int current_i = i;
        for (int j = static_cast<int>(lines) - 1; j >= i; --j) {
            int current_j = j;
            table[current_i++][current_j--] = curr_num++;
        }
    }

    return table;
}
