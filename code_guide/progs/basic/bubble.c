#include "ds.h"

void bubble(int *arr, int size)
{
    int flag;
    for (int i = size - 1; i > 0; i--) {
        flag = 0;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + (j + 1));
                flag = 1;
            }
        }
        if (!flag) break;
    }
}

int main(int argc, char *argv[])
{
    int size = 30;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);
    bubble(arr, size);
    if (!is_sorted(arr, size))
        printf("not sorted!\n");
}
