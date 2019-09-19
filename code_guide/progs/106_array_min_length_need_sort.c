#include "ds.h"

int min_length(int *arr, int size)
{
    int min = arr[size - 1];
    int min_idx = -1;
    for (int i = size - 2; i >= 0; i--) {
        if (arr[i] > min) {
            min_idx = i;
        } else {
            min = arr[i] < min ? arr[i] : min;
        }
    }
    if (min_idx == -1)
        return 0;

    int max = arr[0];
    int max_idx = -1;
    for (int i = 1; i < size; i++) {
        if (arr[i] < max) {
            max_idx = i;
        } else {
            max = arr[i] > max ? arr[i] : max;
        }
    }
    printf("from %d to %d\n", min_idx, max_idx);
    return max_idx - min_idx + 1;
}

int main() 
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 10);
    printArray(arr, size);
    printf("min length %d\n", min_length(arr, size));
}
