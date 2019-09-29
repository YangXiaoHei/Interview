#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

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

    int maxlen = -2147483647-1;
    for (int i = 1; i <= size; i++) {
        for (int j = i; j >= 0; j--) {
            if (sum_arr[j] >= sum_arr[i] - k) {
                maxlen = max(maxlen, i - j);
            }
        }
    }
    free(sum_arr);
    return maxlen;
}

int main()
{
    int arr[] = { 3, -2, -4, 0, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("max length = %d\n", max_length(arr, size, -2));
}
