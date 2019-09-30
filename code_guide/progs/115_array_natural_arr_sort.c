#include "ds.h"

void natural_sort(int *arr, int size)
{
    if (!arr || size <= 0)
        return;
    
    for (int i = 0; i < size; i++) {
        while (arr[i] != i + 1)
            swap(arr + i, arr + arr[i] - 1);
    }
}

int main()
{
    int size = 10;
    int *arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) 
        arr[i] = i + 1;
    shuffle(arr, size);
    printArray(arr, size);
    natural_sort(arr, size);
    printArray(arr, size);
}
