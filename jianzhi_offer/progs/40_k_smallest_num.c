#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int partition(int *arr, int lo, int hi)
{
    if (lo > hi) 
        return -1;
    if (lo == hi)
        return hi;

    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + j, arr + lo);
    return j;
}

int select_k(int *arr, int size, int k)
{
    int lo = 0, hi = size - 1;
    int res = 0;
    while (1) {
        res = partition(arr, lo, hi);
        if (res == k)
            break;
        if (k < res)
            hi = res - 1;
        else
            lo = res + 1;
    }    
    return arr[res];
}

void print_k_smaller(int *arr, int size, int k)
{
    if (!arr)
        return;

    if (size < 0 || k < 0)
        return;

    if (k > size)
        return;

    select_k(arr, size, k);
    for (int i = 0; i < k; i++)
        printf("%-3d", arr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);
    int k = randWithRange(0, size);
    printf("k = %-3d\n", k);
    print_k_smaller(arr, size, k);
}
