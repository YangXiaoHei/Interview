#include "ds.h"

void insertion_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
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

void x_insertion_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;

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

void x_insertion(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    x_insertion_core(arr, 0, size - 1);
}

void binary_insertion_core(int *arr, int lo, int hi)
{
    int size = hi - lo + 1;
    if (size <= 1)
        return;

    for (int i = lo + 1; i <= hi; i++) {
        int target = arr[i];
        int l = lo, h = i;
        int mid;
        while (l < h) {
            mid = l + (h - l) / 2;
            if (arr[mid] >= target) 
                h = mid;
            else
                l = mid + 1;
        }

        for (int j = i - 1; j >= l; j--)
            arr[j + 1] = arr[j];
        arr[l] = target;
    }
}
void binary_insertion(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    binary_insertion_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 100000;
    int *arr = arrayWithRange(size, 0, 100000);
    int *copy = copyArray(arr, size);
    int *copy1 = copyArray(arr, size);
    BENCHMARK(
                insertion(arr, size);
             );
    BENCHMARK(
                x_insertion(copy, size);
             );

    BENCHMARK(
                binary_insertion(copy1, size);
             );

    if (!is_sorted(arr, size))
        printf("not sorted!\n");

    if (!is_sorted(copy, size))
        printf("not sorted!\n");

    if (!is_sorted(copy1, size))
        printf("not sorted!\n");
}
