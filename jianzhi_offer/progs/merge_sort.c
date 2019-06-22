#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tool.h"

void insertion(int *arr, int size, int lo, int hi)
{
    for (int i = lo; i <= hi; i++) {
        int t = arr[i], j;
        for (j = i - 1; j >= lo && t < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = t;
    } 
}

void merge(int *arr, int *aux, int size, int lo, int mid, int hi)
{
    memcpy(aux + lo, arr + lo, sizeof(int) * (hi - lo + 1));
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++)
        if (i > mid)    arr[k] = aux[j++];
        else if (j > hi) arr[k] = aux[i++];
        else if (aux[j] < aux[i]) arr[k] = aux[j++];
        else    arr[k] = aux[i++];
}

void merge_sort_core(int *arr, int *aux, int size, int lo, int hi)
{
    if (hi - lo + 1 < 30) {
        insertion(arr, size, lo, hi);
        return;
    }

    int mid = (hi - lo) / 2 + lo; 
    merge_sort_core(arr, aux, size, lo, mid);
    merge_sort_core(arr, aux, size, mid + 1, hi);
    merge(arr, aux, size, lo, mid, hi);
}

void merge_sort(int *arr, int size)
{
    int *aux = malloc(sizeof(int) * size);
    merge_sort_core(arr, aux, size, 0, size - 1);
    free(aux);
}

int is_sorted(int *arr, int size)
{
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    int size = 10000000;
    int *arr = arrayWithRange(size, 0, 10000000);
    long beg = getCurTime();
    merge_sort(arr, size);
    long end = getCurTime();
    printf("cost = %.3f ms\n", (end - beg) / 1000.0);
    assert(is_sorted(arr, size));
}
