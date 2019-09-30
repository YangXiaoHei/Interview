#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int max_subarr_sum(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int cur = 0, maxsum = -2147483647-1;
    for (int i = 0; i < size; i++) {
        cur += arr[i];
        maxsum = max(maxsum, cur);
        if (cur < 0) 
            cur = 0;
    }
    return maxsum;
}

int main()
{
    int arr[] = { 1, -2, 3, 5, -2, 6, -1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", max_subarr_sum(arr, size));
}
