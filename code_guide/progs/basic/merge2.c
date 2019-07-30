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

int min(int a, int b) { return a < b ? a : b; }

void merge(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int *aux = malloc(sizeof(int) * size);
    memcpy(aux, arr, sizeof(int) * size);

    for (int sz = 1; sz < size; sz *= 2)
        for (int i = 0; i < size - sz; i += 2 * sz)
            merge_sort(arr, aux, i, i + sz - 1, min(i + 2 * sz - 1, size - 1));
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, size * 2);
    BENCHMARK(
    merge(arr, size);
            );
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
