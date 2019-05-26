#include <stdio.h>
#include "array_tool.h"

void merge_two_sorted_array(int *a1, int a1size, int *a2, int a2size)
{
    if (!a1 || !a2 || a1size <= 0 || a2size <= 0)
        return;

    int *a1tail = a1 + a1size - 1;
    int *a2tail = a2 + a2size - 1;
    int total = a1size + a2size;
    int *a1end = a1 + total - 1;
    while (total--) {
        if (*a1tail > *a2tail)
            *a1end-- = *a1tail--;
        else
            *a1end-- = *a2tail--;
    }
}

int main(int argc, char *argv[])
{
    int a1[128] = {1, 3, 7, 9};
    int a2[] = {2, 4, 5, 6, 8, 10};

    int a1size = 4;
    int a2size = 6;

    merge_two_sorted_array(a1, a1size, a2, a2size);

    printArray(a1, a1size + a2size);
}
