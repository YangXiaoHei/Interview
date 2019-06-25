#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

int *gen_arr(int *sz)
{
    int size = *sz;
    int *array = arrayWithRange(size, 0, 40);
    int *copy = copyArray(array, size);
    int *copy1 = copyArray(array, size);

    int *new = malloc(sizeof(int) * size * 3 + 1);
    memcpy(new, array, sizeof(int) * size);
    memcpy(new + size, copy, sizeof(int) * size);
    memcpy(new + 2 * size, copy1, sizeof(int) * size);
    new[3 * size + 1 - 1] = randWithRange(40, 50);
    free(array);
    free(copy);
    free(copy1);
    *sz = size * 3 + 1;
    return new;
}

void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = randWithRange(0, size - i) + i;
        swap(arr + r, arr + i);
    }
}

int find_appear_once(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int bits[32] = { 0 };
    for (int i = 0; i < size; i++) {
        int t = arr[i];
        for (int j = 31; j >= 0; j--) 
            bits[j] += ((t >> j) & 1);
    }

    int num = 0;
    for (int i = 31; i >= 0; i--)
        num |= (bits[i] % 3) << i;

    return num;
}

int main(int argc, char *argv[])
{
    int size = 4;
    int *arr = gen_arr(&size);
    shuffle(arr, size);
    printArray(arr, size);
    
    printf("num = %d\n", find_appear_once(arr, size));
}
