#include "ds.h"

int jump = 2147483647;

void game(int *arr, int size, int idx, int n)
{
    if (idx >= size - 1) {
        if (idx == size - 1 && n < jump) 
           jump = n; 
        return;
    } 

    for (int i = 1; i <= arr[idx]; i++) 
        game(arr, size, idx + i, n + 1);
}

int main(int argc, char *argv[])
{
    int arr[] = { 3, 2, 3, 1, 1, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);

    game(arr, size, 0, 0);

    printf("jump = %d\n", jump);
}
