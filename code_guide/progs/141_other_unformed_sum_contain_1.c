#include "ds.h"

int unformed_one(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    sort(arr, size);

    int range = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] <= range + 1) {
            range += arr[i];
        } else {
            return range + 1;
        }
    }
    return range + 1;
}

int main()
{
    int size = 5;
    int *arr = arrayWithRange(size, 1, 10);
    printArray(arr, size);
    printf("%d\n", unformed_one(arr, size));
}
