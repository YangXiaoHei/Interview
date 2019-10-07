#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int xabs(int a, int b) { return a > b ? a - b : b - a; }

int leftmax_rightmax(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;

    int *larr = malloc(sizeof(int) * size);
    int *rarr = malloc(sizeof(int) * size);
    int lmax = -2147483647-1, rmax = lmax;
    for (int i = 0, j = size - 1; i < size; i++, j--) {
        lmax = max(lmax, arr[i]);
        rmax = max(rmax, arr[j]);
        larr[i] = lmax, rarr[j] = rmax;
    }
    int maxdiff = -2147483647-1;
    for (int k = 0; k <= size - 2; k++) {
        maxdiff = max(maxdiff, xabs(larr[k], rarr[k + 1])); 
    }
    free(larr), free(rarr);
    return maxdiff;
}

int main()
{
    int arr[] = { 2, 7, 3, 1, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", leftmax_rightmax(arr, size));
}
