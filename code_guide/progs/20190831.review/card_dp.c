#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int card(int *arr, int size)
{
    if (!arr || size <= 0)
        return 0;

    int *f = malloc(sizeof(int) * size * size);
    int *s = malloc(sizeof(int) * size * size);
    memset(f, 0, sizeof(int) * size * size);
    memset(s, 0, sizeof(int) * size * size);

#define F(i, j) f[(i) * size + j]
#define S(i, j) s[(i) * size + j]

    for (int j = 0; j < size; j++) {
        F(j, j) = arr[j];
        for (int i = j - 1; i >= 0; i--) {
            F(i, j) = max(arr[i] + S(i + 1, j), S(i, j - 1) + arr[j]);
            S(i, j) = min(F(i + 1, j), F(i, j - 1));
        }
    }
    int res = max(F(0, size - 1), S(0, size - 1));
    free(f);
    free(s);
    return res;
}

int main()
{
    int arr[] = { 1, 2, 100, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", card(arr, size));
}
