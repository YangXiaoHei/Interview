#include "ds.h"

int partition(int *arr, int size, int lo, int hi)
{
    if (lo == hi)
        return lo;

    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + j, arr + lo);
    return j;
}

int select_k(int *arr, int size, int k)
{
    if (!arr || size <= 0 || k < 0 || k >= size)
        return -1;

    int lo = 0, hi = size - 1;    
    while (1) {
        int j = partition(arr, size, lo, hi);
        if (j == k)
            break;

        if (j < k)
            lo = j + 1;
        else
            hi = j - 1;
    }
    return arr[k];
}

int *min_k(int *arr, int size, int k)
{
    int mink = select_k(arr, size, k - 1);
    int *res = malloc(sizeof(int) * k);
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < mink)
            res[j++] = arr[i];
    }

    for (; j < k; j++)
        res[j] = mink;

    return res;
}

int main()
{
    int size = 50;
    int k = 5;
    int *arr = arrayWithRange(size, 0, 20);
    printArray(arr, size);
    printArray(min_k(arr, size, k), k);
}
