#include "ds.h"

void adjust_arr(int *arr, int size)
{
    if (!arr || size < 2)
        return;

    int odd = 1, even = 0;
    do {
        if (arr[size - 1] & 1) {
            swap(arr + size - 1, arr + odd);
            odd += 2;
        } else {
            swap(arr + size - 1, arr + even);
            even += 2;
        }
    } while (odd < size && even < size);
}

int main()
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 10);
    printArray(arr, size);
    adjust_arr(arr, size);
    printArray(arr, size);
}
