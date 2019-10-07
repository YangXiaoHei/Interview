#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int leftmax_rightmax(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int maxv = -2147483647-1;
    for (int i = 0; i < size; i++)
        maxv = max(arr[i], maxv);
    return maxv - min(arr[0], arr[size - 1]);
}

int main()
{
    int arr[] = { 2, 7, 3, 1, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", leftmax_rightmax(arr, size));
}
