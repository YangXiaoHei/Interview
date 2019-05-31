#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int randWithRange(int lo, int hi)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec + tv.tv_sec * 1000000 );
    return rand() % (hi - lo) + lo;
}

void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++) 
        printf("%-4d", array[i]);
    printf("\n");
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
