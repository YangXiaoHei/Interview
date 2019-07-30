#include "ds.h"

void insertion(int *arr, int lo, int hi)
{
    for (int i = lo; i <= hi; i++) {
        int t = arr[i], j;
        for (j = i - 1; j >= lo && t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

void quick(int *arr, int lo, int hi)
{
    if (hi - lo + 1 < 14) {
        insertion(arr, lo, hi);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < arr[lo]) swap(arr + mid, arr + lo);
    if (arr[hi] < arr[lo]) swap(arr + lo, arr + hi);
    if (arr[mid] < arr[hi]) swap(arr + mid, arr + hi);

    int i = lo - 1, j = hi, p = lo - 1, q = hi, pivot = arr[hi];
    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
        if (arr[i] == pivot)
            swap(arr + i, arr + (++p));
        if (arr[j] == pivot)
            swap(arr + j, arr + (--q));
    }
    swap(arr + i, arr + hi);
    int lt = i - 1, gt = i + 1, k = lo, m = hi - 1;
    while (k <= p)
        swap(arr + (k++), arr + (lt--));
    while (m >= q)
        swap(arr + (m--), arr + (gt++));

    quick(arr, lo, lt);
    quick(arr, gt, hi);
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, 100);
    BENCHMARK(
                quick(arr, 0, size - 1);
             );
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
