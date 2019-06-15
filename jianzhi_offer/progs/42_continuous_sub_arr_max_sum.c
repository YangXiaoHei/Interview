#include <stdio.h>
#include "tool.h"

int err_occur = 0;
int sub_arr_max_sum(int *arr, int size)
{
    if (!arr || size <= 0) {
        err_occur = 1;
        return 0;
    }

    int sum = 0x80000000;
    int result = sum;
    for (int i = 0; i < size; i++) {
        if (sum <= 0) 
            sum = arr[i];
        else 
            sum += arr[i];

        if (sum > result) 
            result = sum;
    }
    return result;
}

int main(int argc, char *argv[])
{
    int size = 20;
    int *arr = arrayWithRange(size, -10, 10);
    printArray(arr, size);
    printf("continuous sub array max sum = %-3d\n", sub_arr_max_sum(arr, size));
}
