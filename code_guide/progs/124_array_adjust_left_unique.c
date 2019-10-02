#include "ds.h"

void left_unique(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int u = 0, i = 1;
    while (i < size) {
        if (arr[i++] != arr[u])
            swap(arr + ++u, arr + i - 1);
    }
}

int main()
{
    int size = 20;
    int *arr = arrayWithRange(size, -5, 5);
    sort(arr, size);
    printArray(arr, size);
    left_unique(arr, size);
    printArray(arr, size);
}
