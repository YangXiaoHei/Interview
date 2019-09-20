#include "ds.h"

int odd_once(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int res = 0;
    for (int i = 0; i < size; i++)
        res ^= arr[i];
    return res;
}

int main()
{
    int arr[] = { 1, 1, 2, 2, 3, 3, 3, 4, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    shuffle(arr, size);
    printArray(arr, size);
    printf("%d \n", odd_once(arr, size));
}
