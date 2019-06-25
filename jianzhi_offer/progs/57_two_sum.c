#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

void two_sum(int *arr, int size, int key)
{
    if (!arr || size <= 0)
        return;

    if (size == 1 && key != *arr)
        return;

    int i = 0, j = size - 1;
    while (i < j) {
        int sum = arr[i] + arr[j];
        if (sum == key) {
            printf("%d + %d = %d\n", arr[i], arr[j], key);
            break;
        }
    
        if (sum < key)
            i++;
        else
            j--;
    }
}

int main(int argc, char *argv[])
{
    int size = 20;
    int *arr = arrayWithRange(size, -10, 10); 
    int key = randWithRange(-20, 20);
    tool_sort(arr, size);
    printArray(arr, size);
    printf("key = %d\n", key);
    two_sum(arr, size, key);
}
