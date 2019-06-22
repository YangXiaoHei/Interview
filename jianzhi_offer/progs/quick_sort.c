#include <stdio.h>
#include <assert.h>
#include "tool.h"

void quick_sort(int *arr, int size, int lo, int hi)
{
    if (hi - lo + 1 < 30) {
        for (int i = lo; i <= hi; i++) {
            int t = arr[i], j;
            for (j = i - 1; j >= lo && t < arr[j]; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = t;
        }
        return;
    } 

    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + lo, arr + j);

    quick_sort(arr, size, lo, j - 1);
    quick_sort(arr, size, j + 1, hi);
}

int is_sorted(int *arr, int size)
{
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, 10000000);
    long beg = getCurTime();
    quick_sort(arr, size, 0, size - 1);
    long end = getCurTime();
    printf("cost = %.3f ms\n", (end - beg) / 1000.0);
    assert(is_sorted(arr, size));
}
