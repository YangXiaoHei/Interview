#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

int inversions_sort(int *arr, int *aux, int size, int lo, int mid, int hi)
{
    memcpy(aux + lo, arr + lo, sizeof(int) * (hi - lo + 1));
    int i = lo, j = mid + 1;
    int inversions = 0;
    for (int k = lo; k <= hi; k++)
        if      (i > mid)           arr[k] = aux[j++];
        else if (j > hi)            arr[k] = aux[i++];
        else if (aux[j] < aux[i])   arr[k] = aux[j++], inversions += (mid - i + 1);
        else                        arr[k] = aux[i++];
    return inversions;
}


int inversions_divide(int *arr, int *aux, int size, int lo, int hi)
{
    if (lo >= hi)
        return 0;

    int mid = (hi - lo) / 2 + lo;
    int lbranch = inversions_divide(arr, aux, size, lo, mid);
    int rbranch = inversions_divide(arr, aux, size, mid + 1, hi);
    int cur_merged = inversions_sort(arr, aux, size, lo, mid, hi);
    return lbranch + rbranch + cur_merged;
}

int inversions(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;
    int *aux = malloc(sizeof(int) * size);
    if (!aux) exit(1);
    return inversions_divide(arr, aux, size, 0, size - 1);
}

int inversions_check(int *arr, int size)
{
    int inversions = 0;
    for (int i = 0; i < size; i++) 
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[i])
                inversions++;
    return inversions;
}


int main(int argc, char *argv[])
{
    int size = 100;
    int *arr = arrayWithRange(size, 0, 100);
    int for_check = inversions_check(arr, size);
    printf("inversions = %-3d\n", inversions(arr, size));
    printf("inversions check = %-3d\n", for_check);
}


