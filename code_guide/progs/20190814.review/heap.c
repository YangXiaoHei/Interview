#include "ds.h"

void sink(int *arr, int k, int size)
{
    int t = arr[k - 1];
    while ((k << 1) <= size) {
        int j = k << 1;
        if (j < size && arr[j - 1] < arr[j]) j++;
        if (t >= arr[j - 1]) break;
        arr[k - 1] = arr[j - 1];
        k = j;
    }
    arr[k - 1] = t;;
}

void heap_x(int *arr, int size)
{
    for (int i = size >> 1; i > 0; i--)
        sink(arr, i, size);

    while (size > 1) {
        int t = arr[size - 1];
        arr[size - 1] = arr[0];
        --size;
        int k = 1;
        while ((k << 1) <= size) {
            int j = k << 1;
            if (j < size && arr[j - 1] < arr[j]) j++;
            arr[k - 1] = arr[j - 1];
            k = j;
        }
        arr[k - 1] = t;
        while (k > 1 && t >= arr[(k >> 1) - 1]) {
            arr[k - 1] = arr[(k >> 1) - 1];
            k >>= 1;
        }
        arr[k - 1] = t;
    }
}

void heap(int *arr, int size)
{
    for (int i = size >> 1; i > 0; i--)
        sink(arr, i, size);

    while (size > 1) {
        int t = arr[0];
        arr[0] = arr[size - 1];
        arr[size - 1] = t;
        sink(arr, 1, --size);
    }
}

int main(int argc, char *argv[])
{
    int size = 1000000;
    int *arr = arrayWithRange(size, 0, size);
    int *copy = copyArray(arr, size);
    BENCHMARK(
                heap(arr, size);
             );
    BENCHMARK(
                heap_x(copy, size);
             );
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
    if (!is_sorted(copy, size))
        printf("not sorted!\n");
}
