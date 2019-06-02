#include <stdio.h>
#include "tool.h"
#include <time.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int find_dup(int *a, int size)
{
    if (!a || size <= 1)
        return -1;

    int result = -1;
    for (int i = 0; i < size; i++) {
        while (a[i] != i) {
            if (a[i] == a[a[i]]) {
                result = a[i];
                goto end;
            }
            swap(&a[i], &a[a[i]]);
        }
    }
end:
    return result;
}

int main(int argc, char *argv[])
{
    /*
     * int *array = arrayWithSize(10);
     */
    int array[] = {1, 0, 3, 1, 3};
    printArray(array, 5);
    printf("%d\n", find_dup(array, 5));
}
