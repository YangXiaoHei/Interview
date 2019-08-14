#include "ds.h"

static inline int mid3(int *arr, int i, int j, int k)
{
    return  arr[i] < arr[j] ? 
           (arr[j] < arr[k] ? j : arr[i] < arr[k] ? k : i) :
           (arr[k] < arr[j] ? j : arr[k] < arr[i] ? k : i);
}
void insertion_x(int *arr, int lo, int hi)
{
    int flag = 0;
    for (int i = hi; i > lo; i--) {
        if (arr[i - 1] > arr[i]) {
            int t = arr[i - 1];
            arr[i - 1] = arr[i];
            arr[i] = t;
            flag = 1;
        }
    }
    if (!flag) return;

    for (int i = lo + 2; i <= hi; i++) {
        int t = arr[i], j;
        for (j = i - 1; t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

void quick3way_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;

    if (size < 14) {
        insertion_x(arr, lo, hi);
        return;
    }

    int mid = lo + ((hi - lo) >> 1);
    if (arr[mid] > arr[hi]) swap(arr + mid, arr + hi);
    if (arr[lo] > arr[hi])  swap(arr + lo, arr + hi);
    if (arr[lo] < arr[mid]) swap(arr + lo, arr + mid);

    int pivot = arr[lo];
    int i = lo + 1, lt = lo, gt = hi;
    /* a[lo ... lt - 1] < pivot = a[lt ... gt] < a[gt + 1 ... hi] */
    while (i <= gt) {
        if (arr[i] < pivot)         swap(arr + i++, arr + lt++);
        else if (arr[i] > pivot)    swap(arr + i, arr + gt--);
        else    i++;
    }
    quick3way_core(arr, lo, lt - 1);
    quick3way_core(arr, gt + 1, hi);
}

void quick3way(int *arr, int size)
{
    quick3way_core(arr, 0, size - 1);
}

void quick2way_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;
    if (size < 14) {
        insertion_x(arr, lo, hi);
        return;
    }

    int mid = lo + ((hi - lo) >> 1);
    if (arr[mid] > arr[hi]) swap(arr + mid, arr + hi);
    if (arr[lo] > arr[hi])  swap(arr + lo, arr + hi);
    if (arr[mid] > arr[lo]) swap(arr + mid, arr + lo);

    int pivot = arr[lo], i = lo, j = hi + 1;
    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + lo, arr + j);
    quick2way_core(arr, lo, j - 1);
    quick2way_core(arr, j + 1, hi);
}

void quick2way(int *arr, int size)
{
    quick2way_core(arr, 0, size - 1);
}

void quick3way_x_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
       return; 

    if (size < 14) {
        insertion_x(arr, lo, hi);
        return;
    }

    if (size < 40) {
        int m = mid3(arr, lo, lo + (size >> 1), hi);
        swap(arr + m, arr + lo);
    } else {
        int eps = size >> 3;
        int mid = lo + (size >> 1);
        int m1 = mid3(arr, lo, lo + eps, lo + eps + eps);
        int m2 = mid3(arr, mid - eps, mid, mid + eps);
        int m3 = mid3(arr, hi - eps - eps, hi - eps, hi);
        int n = mid3(arr, m1, m2, m3);
        swap(arr + n, arr + lo);
    }

    int i = lo, j = hi + 1, p = lo, q = hi + 1;
    int pivot = arr[lo];
    int w = 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);

        if (arr[i] == pivot) swap(arr + i, arr + ++p);
        if (arr[j] == pivot) swap(arr + j, arr + --q);
    }
    swap(arr + j, arr + lo);

    int lt = j - 1, gt = j + 1;
    for (int k = lo + 1; k <= p; k++)
        swap(arr + k, arr + lt--);

    for (int k = hi; k >= q; k--)
        swap(arr + k, arr + gt++);

    quick3way_x_core(arr, lo, lt);
    quick3way_x_core(arr, gt, hi);
}

void quick3way_x(int *arr, int size)
{
    quick3way_x_core(arr, 0, size - 1);    
}

int main(int argc, char *argv[])
{
    int size = 1000000;
    int *arr = arrayWithRange(size, 0, size);    
    int *copy = copyArray(arr, size);
    int *copy1 = copyArray(arr, size);

    BENCHMARK(
                quick3way(arr, size);
             );
    BENCHMARK(
                quick2way(copy, size);
             );
    BENCHMARK(
                quick3way_x(copy1, size);
             );

    if (!is_sorted(arr, size))
        printf("not sorted!\n");
    if (!is_sorted(copy, size))
        printf("not sorted!\n");
    if (!is_sorted(copy1, size))
        printf("not sorted!\n");
}
