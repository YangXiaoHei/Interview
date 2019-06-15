#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
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
