#include "ds.h"

void quick_core(int *arr, int lo, int hi)
{
    if (lo >= hi)
        return;

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < arr[lo]) swap(arr + mid, arr + lo);
    if (arr[hi] < arr[lo]) swap(arr + hi, arr + lo);
    if (arr[mid] < arr[hi]) swap(arr + mid, arr + hi);

    int pivot = arr[hi], i = lo - 1, j = hi;
    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + hi, arr + i);

    quick_core(arr, lo, i - 1);
    quick_core(arr, i + 1, hi);
}

void quick(int *arr, int size)
{
    if (!arr || size <= 1)
        return;

    quick_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 100;
    int *arr = arrayWithRange(size, 0, 100);
    quick(arr, size);
    if (!is_sorted(arr, size))
        printf("not sorted!");
}
