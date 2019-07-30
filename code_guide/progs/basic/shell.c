#include "ds.h"

void shell_core(int *arr, int lo, int hi)
{
    int h = 1;
    int size = hi - lo + 1;
    while (h < size / 3)
        h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h + lo; i <= hi; i++) {
            int t = arr[i], j;
            for (j = i - h; j >= lo && t < arr[j]; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = t;
        }
        h /= 3;
    }
}

void shell(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    shell_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, size * 2);
    BENCHMARK(
                shell(arr, size);
             );
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
