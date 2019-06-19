#include <stdlib.h>
#include <stdio.h>
#include "tool.h"

void shift(int *input, int len, int dist)
{
    if (!input || len <= 0 || dist < 0 || dist % len == 0)
        return;

    dist %= len;
    int i = 0, j = len - 1;
    while (i < j) 
        swap(input + i++, input + j--);

    i = 0; j = dist - 1;
    while (i < j)
        swap(input + i++, input + j--);

    i = dist; j = len - 1;
    while (i < j)
        swap(input + i++, input + j--);
}

int main(int argc, char *argv[])
{
    int r = randWithRange(1, 50);
    printf("right shift %-3d\n", r);
    int size = 10;
    int *arr = array(size);
    printArray(arr, size);
    shift(arr, size, r);
    printArray(arr, size);
}
