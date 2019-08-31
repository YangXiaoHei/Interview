#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int jump = 2147483647;
void game_core(int *arr, int size, int idx, int n)
{
    if (idx >= size - 1) {
        jump = min(jump, n);
        return;
    }

    for (int i = 1; i <= arr[idx]; i++)
        game_core(arr, size, idx + i, n + 1);
}

void game(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    game_core(arr, size, 0, 0);
}

int main(int argc, char *argv[])
{
    int arr[] = { 3, 2, 3, 1, 1, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    game(arr, size);
    printf("jump = %d\n", jump);
}
