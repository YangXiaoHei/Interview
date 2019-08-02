#include "ds.h"

int xabs(int a, int b) { 
    int diff = a - b;
    return diff < 0 ? -diff : diff;
}

int is_valid(int *record, int i, int j)
{
    for (int k = 0; k < i; k++) {
        if (record[k] == j || xabs(k, i) == xabs(record[k], j))
            return 0;
    }
    return 1;
}

int n_queen_core(int *record, int n, int i)
{
    if (i == n) {
        // draw
        return 1;
    }

    int res = 0;
    for (int j = 0; j < n; j++) {
        if (is_valid(record, i, j)) {
            record[i] = j;
            res += n_queen_core(record, n, i + 1);
        }
    }
    return res;
}

int n_queen(int n)
{
    int *record = malloc(sizeof(int) * n);
    if (!record) exit(1);
    memset(record, 0, sizeof(int) * n);
    return n_queen_core(record, n, 0);
}

int main(int argc, char *argv[])
{
    printf("%d\n", n_queen(8));
}
