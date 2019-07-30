#include "ds.h"

void insertion_core(int *arr, int lo, int hi)
{
    if (lo >= hi)
        return;

    for (int i = lo + 1; i <= hi; i++) {
        int t = arr[i], j;
        for (j = i - 1; j >= lo && t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

void insertion(int *arr, int size)
{
    if (!arr || size <= 0)
        return;
    insertion_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);
    insertion(arr, size);
    printArray(arr, size);
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
