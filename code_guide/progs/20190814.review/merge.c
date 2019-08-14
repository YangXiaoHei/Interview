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

void binary_insertion(int *arr, int lo, int hi)
{
    for (int i = lo + 1; i <= hi; i++) {
        int target = arr[i];
        int l = lo, h = i;
        int m;
        while (l < h) {
            m = (h + l) >> 1;
            if (arr[m] >= target)
                h = m;
            else
                l = m + 1;
        }
        for (int j = i; j > l; j--)
            arr[j] = arr[j - 1];
        arr[l] = target;
    }
}

void merge_x(int *src, int *dst, int lo, int mid, int hi)
{
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++)
        if (i > mid)                dst[k] = src[j++];
        else if (j > hi)            dst[k] = src[i++];
        else if (src[j] < src[i])   dst[k] = src[j++];
        else                        dst[k] = src[i++];    
}

void merge_sort_x_core(int *src, int *dst, int lo, int hi)
{
    int size = hi - lo + 1;    
    if (size <= 1)
        return;
    if (size < 8) {
        /* insertion(dst, lo, hi); */
        insertion_x(dst, lo, hi);
        /* binary_insertion(dst, lo, hi); */
        return;
    }
    int mid = lo + ((hi - lo) >> 1);
    merge_sort_x_core(dst, src, lo, mid);
    merge_sort_x_core(dst, src, mid + 1, hi);
    
    if (src[mid] <= src[mid + 1]) {
        memcpy(dst + lo, src + lo, sizeof(int) * size);
        return;
    }
    merge_x(src, dst, lo, mid, hi);
}

void merge_sort_x(int *arr, int size)
{
    int *aux = malloc(sizeof(int) * size);
    memcpy(aux, arr, sizeof(int) * size);
    merge_sort_x_core(aux, arr, 0, size - 1);
    free(aux);
}

void merge(int *arr, int *aux, int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; i++) 
        aux[i] = arr[i];
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) 
        if (i > mid)                arr[k] = aux[j++];
        else if (j > hi)            arr[k] = aux[i++];
        else if (aux[j] < aux[i])   arr[k] = aux[j++];
        else                        arr[k] = aux[i++];
}

void merge_sort_core(int *arr, int *aux, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;
    if (size < 8) {
        /* insertion(arr, lo, hi); */
        insertion_x(arr, lo, hi);
        /* binary_insertion(arr, lo, hi); */
        return;
    }
    int mid = lo + ((hi - lo) >> 1);
    merge_sort_core(arr, aux, lo, mid);
    merge_sort_core(arr, aux, mid + 1, hi);
    merge(arr, aux, lo, mid, hi);
}

void merge_sort(int *arr, int size)
{
    int *aux = malloc(sizeof(int) * size);
    merge_sort_core(arr, aux, 0, size - 1);
    free(aux);
}

int main(int argc, char *argv[])
{
    int size = 1000000;
    int *arr = arrayWithRange(size, 0, size);
    int *copy = copyArray(arr, size);
    BENCHMARK(merge_sort(arr, size););
    BENCHMARK(merge_sort_x(copy, size););

    if (!is_sorted(arr, size))
        printf("not sorted!\n");

    if (!is_sorted(copy, size))
        printf("not sorted!\n");
}
