#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int f(int *, int, int);
int s(int *, int, int);

int s(int *arr, int i, int j)
{
    if (i == j)
        return 0;

    return min(f(arr, i + 1, j), f(arr, i, j - 1));
}

int f(int *arr, int i, int j)
{
    if (i == j)
        return arr[i];

    return max(s(arr, i + 1, j) + arr[i], s(arr, i, j - 1) + arr[j]);
}

int card_game(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    return max(f(arr, 1, size - 1), f(arr, 0, size - 2));
}

int main(int argc, char *argv[])
{
    int card[] = { 1, 100, 4, 2 };
    int size = sizeof(card) / sizeof(card[0]);
    printf("%d\n", card_game(card, size));
}
