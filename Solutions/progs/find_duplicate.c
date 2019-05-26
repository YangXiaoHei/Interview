#include <stdio.h>
#include "array_tool.h"
#include <time.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int find_duplicate(int *a, int size)
{
    if (!a || size <= 1)
        return -1;

    int result = -1;
    for (int i = 0; i < size; i++) {
        if (a[i] == i)
            continue;
        if (a[i] == a[a[i]]) {
            result = a[i];
            break;
        }
        do {
            swap(&a[i], &a[a[i]]);
        } while (a[i] != a[a[i]]);
    }
    return result;
}

int main(int argc, char *argv[])
{
    int *array = arrayWithSize(10);
    printArray(array, 10);
    printf("%d\n", find_duplicate(array, 10));
}
