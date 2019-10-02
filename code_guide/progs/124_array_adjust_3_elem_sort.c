#include "ds.h"

void elem_3_sort(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int l = -1, r = size;
    int idx = 0;
    while (idx < r) {
        if (arr[idx] == 1)  idx++;
        else if (arr[idx] == 0) swap(arr + ++l, arr + idx++);
        else if (arr[idx] == 2) swap(arr + --r, arr + idx);
        else exit(-1);
    }
}

int main()
{
    int size = 5;
    int *arr = arrayWithRange(size, 0, 3);
    printArray(arr, size);
    elem_3_sort(arr, size);
    printArray(arr, size);
}
