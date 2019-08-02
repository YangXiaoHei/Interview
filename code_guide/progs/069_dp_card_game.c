#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int card_game(int *arr, int size)
{
    int *f = malloc(sizeof(int) * size * size);
    int *s = malloc(sizeof(int) * size * size);
    memset(f, 0, sizeof(int) * size * size);
    memset(s, 0, sizeof(int) * size * size);

#define F(i, j) f[(i) * size + j]
#define S(i, j) s[(i) * size + j]

    for (int i = 0; i < size; i++) {
        F(i, i) = arr[i];
        for (int j = i - 1; j >= 0; j--) {
            F(j, i) = max(arr[j] + S(j + 1, i), arr[i] + S(j, i - 1)); 
            S(j, i) = min(F(j + 1, i), F(j, i - 1));
        }
    }

    int res = max(F(0, size - 1), S(0, size - 1));
    free(f);
    free(s);
    return res;
}

int main(int argc, char *argv[])
{
    int card[] = { 1, 100, 4, 2 };
    int size = sizeof(card) / sizeof(card[0]);
    printf("%d\n", card_game(card, size));
}
