#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int leftmost_idx(int *arr, int size, int k)
{
    int lo = 0, hi = size - 1;
    int res = -1;
    int mid = -1;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2; 
        if (arr[mid] >= k) {
            res = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return res;
}

int max_length(int *arr, int size, int k)
{
    if (!arr || size <= 0)
        return -1;

    // gen sum arr
    int *sum_arr = malloc(sizeof(int) * (size + 1));
    sum_arr[0] = 0;
    for (int i = 0; i < size; i++) {
        sum_arr[i + 1] = sum_arr[i] + arr[i];
    }

    // gen help arr
    int *help_arr = malloc(sizeof(int) * (size + 1));
    int m = sum_arr[0];
    for (int i = 1; i <= size; i++) {
        m = max(m, sum_arr[i]);
        help_arr[i] = m;
    }

    int maxlen = -2147483647-1;
    for (int i = 1; i <= size; i++) {
        int idx = leftmost_idx(help_arr, i, sum_arr[i] - k);
        if (idx == -1)
            continue;
        maxlen = max(maxlen, i - idx);
    }
    free(sum_arr);
    free(help_arr);
    return maxlen;
}

int main()
{
    int size = 7;
    int *arr = arrayWithRange(size, -10, 10);
    printArray(arr, size);
    int k = randWithRange(-5, 5);
    printf("k = %d len = %d\n", k, max_length(arr, size, k));
}
