#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

void reorder(int *arr, int size)
{
    if (!arr || size <= 1) return;
    int lo = 0, hi = size - 1;
    int i = -1, j = hi + 1;
    while (1) {
        while (i < hi && (arr[++i] & 1));
        while (j > lo && !(arr[--j] & 1));
        if (i >= j) break;
        swap(&arr[i], &arr[j]);
    }
}

int main(int argc, char *argv[])
{
    int *arr = arrayWithRange(30, 1, 20);
    reorder(arr, 30);
    printArray(arr, 30);
}
