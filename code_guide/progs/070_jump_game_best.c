#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int jump_game(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    for (int i = 0; i < size; i++)
        if (arr[i] <= 0)
            return 0;

    int cur = 0;
    int next = 0;
    int jump = 0;
    for (int i = 0; i < size; i++) {
        if (cur < i) {
            jump++;
            cur = next;
        }
        next = max(next, i + arr[i]);
    }
    return jump;
}

int main(int argc, char *argv[])
{
    int card[] = { 3, 2, 3, 1, 1, 4 };
    int size = sizeof(card) / sizeof(card[0]);
    printArray(card, size);
    int res = jump_game(card, size);
    printf("res = %d\n", res);
}
