#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

typedef int (*comparator)(const char *, const char *);

void sort_core(char **arr, comparator cmp, int lo, int hi)
{
    if (lo >= hi)
        return;

    char *pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && cmp(arr[++i], pivot) < 0);
        while (j > lo && cmp(arr[--j], pivot) > 0);
        if (i >= j) break;
        char *tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    char *tmp = arr[j];
    arr[j] = arr[lo];
    arr[lo] = tmp;

    sort_core(arr, cmp, lo, j - 1);
    sort_core(arr, cmp, j + 1, hi);
}

char left_buf[128];
char right_buf[128];
int special_compare(const char *a, const char *b)
{
    strcpy(left_buf, a);
    strcat(left_buf, b);

    strcpy(right_buf, b);
    strcat(right_buf, a);

    return strcmp(left_buf, right_buf);
}

void sort(char **arr, int size)
{
    if (!arr || size <= 1)
        return;    

    sort_core(arr, special_compare, 0, size - 1);
}

void convert_to_str_arr(int *arr, int size, char ***strarr)
{
    if (!strarr)
        return;

    char **ptr = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++) {
        ptr[i] = malloc(128);
        snprintf(ptr[i], 128, "%d", arr[i]); 
    }
    *strarr = ptr;
}

void combinate_smallest_num(int *arr, int size)
{
    if (!arr || size <= 1)
        return;

    char **ptr = NULL;
    convert_to_str_arr(arr, size, &ptr);

    sort(ptr, size);

    for (int i = 0; i < size; i++)
        printf("%s", ptr[i]);
    printf("\n");

    for (int i = 0; i < size; i++)
        free(ptr[i]);
    free(ptr);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 30);
    printArray(arr, size);
    combinate_smallest_num(arr, size);
}
