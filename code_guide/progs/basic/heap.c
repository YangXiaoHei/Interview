#include "ds.h"

static inline int less(int *arr, int i, int j)
{
    return arr[i - 1] < arr[j - 1];
}

static inline void exch(int *arr, int i, int j)
{
    int t = arr[i - 1];
    arr[i - 1] = arr[j - 1];
    arr[j - 1] = t;
}

// 小的沉下去，大的浮上来
void sink(int *arr, int k, int size)
{
    while ((k << 1) <= size) {
        int j = k << 1;
        if (j < size && less(arr, j, j + 1)) j++;
        if (!less(arr, k, j)) break;
        exch(arr, k, j);
        k = j;
    }
}

void heap(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    for (int k = size / 2; k >= 1; k--)
        sink(arr, k, size);

    while (size > 1) {
        exch(arr, 1, size--);
        sink(arr, 1, size);
    }
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, size * 2);
    BENCHMARK (
                heap(arr, size);
              );
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
