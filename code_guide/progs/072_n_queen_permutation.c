#include "ds.h"

int xabs(int a, int b) {
    int diff = a - b;
    return diff < 0 ? -diff : diff;
}

int is_valid(int *record, int n)
{
    for (int i = 0; i < n; i++) 
        for (int j = i + 1; j < n; j++) 
            if (xabs(j, i) == xabs(record[j], record[i]))
                return 0;
    return 1;
}

int n_queen_core(int *record, int n, int idx)
{
    if (idx >= n - 1) 
        return is_valid(record, n);

    int res = 0;
    for (int i = idx; i < n; i++) {
        swap(record + idx, record + i);
        res += n_queen_core(record, n, idx + 1);
        swap(record + idx, record + i);
    } 
    return res;
}

int n_queen(int n)
{
    if (n < 0)
        return 0;
    if (n == 1)
        return 1;

    int *record = malloc(sizeof(int) * n);
    if (!record) exit(1);
    for (int i = 0; i < n; i++)
        record[i] = i;
    int res = n_queen_core(record, n, 0);
    free(record);
   return res; 
}

int main(int argc, char *argv[])
{
    printf("%d\n", n_queen(8));
}
