#include "ds.h"

void squint_print(int *m, int r, int c)
{
    if (!m || r <= 0 || c <= 0)
        return;

    int begi = 0, begj = 0;
    int i, j;
    while (begi <= r - 1) {
        i = begi, j = begj;
        while (j >= 0 && i <= r - 1) {
            printf("%-3d", m[i * c + j]);
            j--, i++;
        }
        if (begj == c - 1)
            begi++;
        else
            begj++;
    }
    printf("\n");
}

int main()
{
    int r = randWithRange(1, 10);
    int c = randWithRange(1, 10);
    int *m = matrix_gen_(r, c);
    matrix_print_(m, r, c);
    squint_print(m, r, c);
}
