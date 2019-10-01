#include "ds.h"

int partial_min(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    if (size == 1)
        return 0;

    if (size == 2) 
        return arr[0] < arr[1] ? 0 : 1;

    if (arr[0] < arr[1])
        return 0;

    if (arr[size - 1] < arr[size - 2])
        return size - 1;

    int lo = 1, hi = size - 2;
    int mid = -1;
    while (lo < hi) {
        mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[mid - 1])
            hi = mid - 1;
        else  if (arr[mid] > arr[mid + 1])
            lo = mid + 1;
        else
            return mid;
    }
    return lo;
}

int main()
{
    int size = randWithRange(0, 10);
    int *arr = arrayNoDupWithRange(size, -10, 10);
    printArray(arr, size);
    int index = partial_min(arr, size);
    if (index >= 0)
        printf("index %d, value = %d\n", index, arr[index]); 
}
