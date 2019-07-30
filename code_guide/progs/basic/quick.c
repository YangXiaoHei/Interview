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

void quick(int *arr, int lo, int hi)
{
    if (hi - lo + 1 < 14) {
        insertion(arr, lo, hi);
        return;
    }

    // 三取样切分
    int mid = lo + (hi - lo) / 2;
    // 保证 lo 不是最大
    if (arr[mid] < arr[lo]) swap(arr + mid, arr + lo);
    // 保证 lo 是最小
    if (arr[hi] < arr[lo]) swap(arr + lo, arr + hi);
    // 保证 hi 是中间, mid 是最大
    if (arr[mid] < arr[hi]) swap(arr + mid, arr + hi);

    int pivot = arr[hi], i = lo - 1, j = hi;
    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + i, arr + hi);
    quick(arr, lo, i - 1);
    quick(arr, i + 1, hi);
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
