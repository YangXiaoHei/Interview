#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

int *gen_arr(int *sz)
{
    int size = *sz;
    int *array = arrayWithRange(size, 0, 40);
    int *copy = copyArray(array, size); 

    int *new = malloc(sizeof(int) * size * 2 + 2);
    memcpy(new, array, sizeof(int) * size);
    memcpy(new + size, copy, sizeof(int) * size);
    new[2 * size + 2 - 1] = randWithRange(40, 50);
    new[2 * size + 2 - 2] = randWithRange(50, 60);
    free(array);
    free(copy);
    *sz = size * 2 + 2;
    return new;
}

void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = randWithRange(0, size - i) + i;
        swap(arr + r, arr + i);
    }
}

void find_appear_once_two_num(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int sum = 0;
    for (int i = 0; i < size; i++)
        sum ^= arr[i];

    int rightmost_one = sum & -sum;

    int num1 = 0, num2 = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] & rightmost_one)
            num1 ^= arr[i];
        else
            num2 ^= arr[i];
    }
    printf("num1 = %d num2 = %d\n", num1, num2);
}

int main(int argc, char *argv[])
{
    int size = 5;
    int *arr = gen_arr(&size);
    shuffle(arr, size);
    printArray(arr, size); 
    find_appear_once_two_num(arr, size);
}
