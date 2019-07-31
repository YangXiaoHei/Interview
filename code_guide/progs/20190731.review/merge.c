#include "ds.h"

void merge_sort(int *arr, int *aux, int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; i++)
        aux[i] = arr[i];

    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)                arr[k] = aux[j++];
        else if (j > hi)            arr[k] = aux[i++];
        else if (aux[j] < aux[i])   arr[k] = aux[j++];
        else                        arr[k] = aux[i++];
    }
}

void merge_core(int *arr, int *aux, int lo, int hi)
{
    if (lo >= hi)
        return;

    int mid = lo + (hi - lo) / 2;
    merge_core(arr, aux, lo, mid);
    merge_core(arr, aux, mid + 1, hi);
    merge_sort(arr, aux, lo, mid, hi);
}

void merge(int *arr, int size)
{
    int *aux = malloc(sizeof(int) * size);
    memcpy(aux, arr, sizeof(int) * size);
    merge_core(arr, aux, 0, size - 1);
    free(aux); 
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);    
    merge(arr, size);
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
