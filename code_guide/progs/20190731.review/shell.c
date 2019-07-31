#include "ds.h"

void shell(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int h = 1;
    while (h < size / 3)
        h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < size; i++) {
            int t = arr[i], j;
            for (j = i - h; j >= 0 && t < arr[j]; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = t;
        }
        h /= 3;
    }
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);

    shell(arr, size);

    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
