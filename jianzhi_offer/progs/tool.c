#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "tool.h"

void tool_sort_core(int *arr, int size, int lo, int hi)
{
    if (hi - lo + 1 < 30) {
        for (int i = lo; i <= hi; i++) {
            int t = arr[i], j;
            for (j = i - 1; j >= lo && t < arr[j]; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = t;
        }
        return;
    }

    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + lo, arr + j);

    tool_sort_core(arr, size, lo, j - 1);
    tool_sort_core(arr, size, j + 1, hi);
}

void tool_sort(int *arr, int size)
{
    if (!arr || size <= 1)
       return; 

    tool_sort_core(arr, size, 0, size - 1);
}

int tool_is_sorted(int *arr, int size)
{
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return 0;
    return 1;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

long getCurTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void parseArray(int *arr, int *len, char *str)
{
    if (!arr || !len || *len <= 0 || !str) return;
    char *p = str, *q = p;
    int i = 0, n = 0;
    while (*p && *p >= '0' && *p <= '9' && i < *len) {
        n = strtol(q, &p, 10);
        arr[i++] = n;
        while (*p && (*p < '0' || *p > '9')) p++;
        if (!*p) break;
        q = p;
    }
    *len = i;
}


int randWithRange(int lo, int hi)
{
    if (lo == hi)
        return 0;
    usleep(19);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec + tv.tv_sec * 1000000);
    return rand() % (hi - lo) + lo;
}

void printArray(int *array, int size)
{
    printf("size=%d\n", size);
    for (int i = 0; i < size; i++) 
        printf("%-4d", array[i]);
    printf("\n");
}

int *copyArray(int *arr, int size)
{
    int *copy = malloc(sizeof(int) * size);
    memcpy(copy, arr, sizeof(int) * size);
    return copy;
}

int *array(int size)
{
    int *array = malloc(sizeof(int) * size);
    if (!array) {
        printf("memory alloc fail!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) 
        array[i] = i;
    return array;
}

int *arrayWithRange(int size, int lo, int hi)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    int *array = malloc(sizeof(int) * size);
    if (!array) {
        printf("memory alloc fail!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        int elem = rand() % (hi - lo) + lo;
        array[i] = elem; 
    }
    return array;
}

int *arrayWithSize(int size)
{
    return arrayWithRange(size, 0, size);
}
