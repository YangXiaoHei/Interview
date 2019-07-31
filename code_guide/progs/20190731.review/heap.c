#include "ds.h"

static inline void exch(int *arr, int i, int j)
{
    int t = arr[i - 1];
    arr[i - 1] = arr[j - 1];
    arr[j - 1] = t;
}

static inline void sink(int *arr, int i, int size)
{
    int t = arr[i - 1];
    while (2 * i <= size) {
        int j = 2 * i;
        if (j < size && arr[j - 1] < arr[j]) j++;
        if (t >= arr[j - 1]) break;
        arr[i - 1] = arr[j - 1];
        i = j;
    }
    arr[i - 1] = t;
}

void heap(int *arr, int size)
{
    if (!arr || size <= 1)
        return;

    for (int i = size / 2; i >= 1; i--)
        sink(arr, i, size);

    while (size > 1) {
        exch(arr, 1, size--);
        sink(arr, 1, size);
    }
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);

    heap(arr, size);

    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
