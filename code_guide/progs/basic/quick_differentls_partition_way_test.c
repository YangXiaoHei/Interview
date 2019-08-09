#include "ds.h"

void insertion(int *arr, int lo, int hi)
{
    for (int i = lo; i <= hi; i++) {
        int t = arr[i], j;
        for (j = i - 1; j >= 0 && t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

void quick_B_core(int *arr, int lo, int hi)
{
    if (hi - lo + 1 < 14) {
        insertion(arr, lo, hi);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < arr[lo]) swap(arr + lo, arr + mid);
    if (arr[hi] < arr[lo])  swap(arr + hi, arr + lo);
    if (arr[mid] < arr[hi]) swap(arr + mid,arr + hi);

    int pivot = arr[hi], i = lo - 1, j = hi;
    while (i < j) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + i, arr + hi);

    quick_B_core(arr, lo, i - 1);
    quick_B_core(arr, i + 1, hi);
}

void quick_B(int *arr, int size)
{
    return quick_B_core(arr, 0, size - 1);
}

void quick_A_core(int *arr, int lo, int hi)
{
    if (hi - lo + 1 < 14) {
        insertion(arr, lo, hi);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < arr[lo]) swap(arr + lo, arr + mid);
    if (arr[hi] < arr[lo])  swap(arr + hi, arr + lo);
    if (arr[mid] < arr[hi]) swap(arr + mid,arr + hi);

    int pivot = arr[hi], i = lo, j = hi;
    while (i < j) {
        while (i < j && arr[i] <= pivot) i++;
        if (i < j)
            arr[j] = arr[i];

        while (i < j && arr[j] >= pivot) j--;
        if (i < j)
            arr[i] = arr[j];
    }
    arr[i] = pivot;

    quick_A_core(arr, lo, i - 1);
    quick_A_core(arr, i + 1, hi);
}

void quick_A(int *arr, int size)
{
    return quick_A_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, 10000000);
    int *copy = copyArray(arr, size);

    BENCHMARK(quick_A(arr, size););
    BENCHMARK(quick_B(copy, size););

    if (!is_sorted(arr, size))
        printArray(arr, size);
    if (!is_sorted(copy, size))
        printArray(copy, size);
}
