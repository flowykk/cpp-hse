#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    const int table_size = 10;
    int curr_num = 0;

    for (int i = 0; i < table_size; ++i) {
        int current_i = i;
        for (int j = 0; j < i + 1; ++j) {
            int current_j = j;
            table[current_j--][current_i--] = curr_num++;
        }
    }

    for (int i = 1; i < table_size; ++i) {
        int current_i = i;
        for (int j = table_size - 1; j >= i; --j) {
            int current_j = j;
            table[current_i++][current_j--] = curr_num++;
        }
    }
}
