#include <stdio.h>
#include "tool.h"

int find_missing_num(int *arr, int size)
{
    int lo = 0, hi = size - 1;
    while (lo < hi) {
        int mid = (hi - lo) / 2 + lo;
        if (arr[mid] != mid)
            hi = mid;
        else
            lo = mid + 1;
    }
    return arr[lo] == lo ? -1 : lo;
}

void modify_arr(int *arr, int *size)
{
    int r = randWithRange(0, *size);
    for (int i = r + 1; i < *size; i++)
        arr[i - 1] = arr[i];
    --*size;
    printf("discard %-3d\n", r);
}

int main(int argc, char *argv[])
{
    int size = 30;
    int *arr = array(size);
    modify_arr(arr, &size);
    printf("missing num is %-3d\n", find_missing_num(arr, size));
}
