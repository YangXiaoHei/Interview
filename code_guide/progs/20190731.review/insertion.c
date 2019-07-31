#include "ds.h"

void insertion(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    for (int i = 1; i < size; i++) {
        int t = arr[i], j;
        for (j = i - 1; j >= 0 && t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);

    insertion(arr, size);

    if (!is_sorted(arr, size))
        printf("not sorted!\n");

}
