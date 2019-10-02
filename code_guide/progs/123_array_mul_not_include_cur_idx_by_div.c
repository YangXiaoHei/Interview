#include "ds.h"

void max_product(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int count0 = 0;
    int mulnot0 = 1;
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0)
            mulnot0 *= arr[i];
        else
            count0++;
    }

    if (count0 > 1) {
        for (int i = 0; i < size; i++) {
            printf("%-10c", '0');
        }
        printf("\n");
        return;
    }

    if (count0 == 1) {
        for (int i = 0; i < size; i++) {
            if (arr[i] != 0) {
                printf("%-10c", '0');
            } else {
                printf("%-10d", mulnot0);
            }
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%-10d", mulnot0 / arr[i]);
    }
    printf("\n");
}

int main()
{
    int size = 10;
    int *arr = arrayWithRange(size, -5, 5);
    printArray(arr, size);
    max_product(arr, size);
}
