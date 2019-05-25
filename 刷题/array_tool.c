#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++) 
        printf("%-4d", array[i]);
    printf("\n");
}

int *arrayWithRange(int size, int lo, int hi)
{
    srand(time(NULL));
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
