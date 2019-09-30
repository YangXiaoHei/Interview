#include "ds.h"

int res = 0;

void merge(int *arr, int *aux, int size, int lo, int mid, int hi)
{
    for (int k = lo; k <= hi; k++)
        aux[k] = arr[k];

    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)                arr[k] = aux[j++];
        else if (j > hi)            arr[k] = aux[i++];
        else if (aux[j] < aux[i])   arr[k] = aux[j++];
        else                        {
            res += aux[i] * (hi - j + 1);
            arr[k] = aux[i++];
        }
    }
}

void min_sum_core(int *arr, int *aux, int size, int lo, int hi)
{
    if (lo >= hi)
        return;

    int mid = lo + (hi - lo) / 2;
    min_sum_core(arr, aux, size, lo, mid);
    min_sum_core(arr, aux, size, mid + 1, hi);
    merge(arr, aux, size, lo, mid, hi);
}

int min_sum(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    res = 0;
    int *aux = malloc(sizeof(int) * size);
    min_sum_core(arr, aux, size, 0, size - 1);
    free(aux);
    return res;
}

int main()
{
    int arr[] = { 1, 3, 5, 2, 4, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", min_sum(arr, size));
}
