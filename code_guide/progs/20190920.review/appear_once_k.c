#include "ds.h"

void appear_once(int *arr, int size, int k)
{
    int res[32] = { 0 };
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 32; j++) {
            res[j] += (arr[i] >> j) & 1;
        }
    }
    int ret = 0;
    for (int i = 0; i < 32; i++) {
        ret |= (res[i] % k) << i;
    }
    printf("ret = %d\n", ret);
}

int main()
{
    int arr[] = { 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 8, 8, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    shuffle(arr, size);
    printArray(arr, size);
    appear_once(arr, size, 3);
}
