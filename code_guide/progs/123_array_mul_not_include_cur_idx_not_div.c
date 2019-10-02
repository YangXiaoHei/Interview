#include "ds.h"

void max_product(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    int *l = malloc(sizeof(int) * size);
    int *r = malloc(sizeof(int) * size);
    l[0] = arr[0], r[size - 1] = arr[size - 1];

    for (int i = 1, j = size - 2; i < size; i++, j--) {
        l[i] = l[i - 1] * arr[i];
        r[j] = r[j + 1] * arr[j]; 
    } 
    int *res = malloc(sizeof(int) * size);
    res[0] = r[1], res[size - 1] = l[size - 2];
    for (int i = 1; i < size - 1; i++) {
        res[i] = l[i - 1] * r[i + 1];
    }
    for (int i = 0; i < size; i++) {
        printf("%-10d", res[i]);
    }
    printf("\n");
    free(res);
    free(l);
    free(r);
}

int main()
{
    int size = 7;
    int *arr = arrayWithRange(size, -5, 5);
    printArray(arr, size);
    max_product(arr, size);
}
