#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int f(int *, int, int);
int s(int *, int, int);

int f(int *arr, int i, int j)
{
    if (i == j)
        return arr[i];

    return max(arr[i] + s(arr, i + 1, j), s(arr, i, j - 1) + arr[j]);
}

int s(int *arr, int i, int j)
{
    if (i == j)
        return 0;

    return min(f(arr, i + 1, j), f(arr, i, j - 1));
}

int card(int *arr, int size)
{
    if (!arr || size <= 0)
       return 0; 

    return max(f(arr, 0, size - 1), s(arr, 0, size - 1));
}

int main() 
{
    int arr[] = { 1, 2, 100, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", card(arr, size));
}
