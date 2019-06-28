#include <stdio.h>
#include <stdlib.h>

int stock_max_profit(int *arr, int size)
{
    int max = -2147483648, min = 2147483647;
    for (int i = 0; i < size; i++) {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    return max - min;
}

int main(int argc, char *argv[])
{
    int arr[] = { 9, 11, 8, 5, 7, 12, 16, 14 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", stock_max_profit(arr, size));
}
