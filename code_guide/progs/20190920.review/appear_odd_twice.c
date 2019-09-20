#include "ds.h"

void odd_twice(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int split = 0;
    for (int i = 0; i < size; i++)
        split ^= arr[i];

    int j = 0;
    while (j < 32 && ((split >> j) & 1) == 0)
       j++; 

    int a = 0, b = 0;
    for (int i = 0; i < size; i++) {
        if ((arr[i] >> j) & 1) {
            a ^= arr[i];
        } else {
            b ^= arr[i];
        }
    }
    printf("%d %d\n", a, b);
}

int main()
{
    int arr[] = { 1, 1, 2, 2, 3, 3, 3, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8, 8, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    shuffle(arr, size);
    printArray(arr, size);
    odd_twice(arr, size); 
}
