#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int find_value_equal_to_index(int *arr, int size)
{
    int lo = 0, hi = size - 1;
    while (lo < hi) {
        int mid = (hi - lo) / 2 + lo;
        if (mid < arr[mid])
            lo = mid + 1;
        else if (mid > arr[mid])
            hi = mid;
        else return mid;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int lo = -3, hi = 10;
    int *arr = arrayWithRange(size, lo, hi);
    tool_sort(arr, size);
    printArray(arr, size);
    printf("index = %-3d\n", find_value_equal_to_index(arr, size));
}
