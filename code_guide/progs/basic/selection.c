#include "ds.h"

void selection(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[min])
                min = j;
        if (min != i)
            swap(arr + i, arr + min);
    }
}

int main(int argc, char *argv[])
{
    int size = 50;
    int *arr = arrayWithRange(size, 0, 100);
    selection(arr, size);
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
