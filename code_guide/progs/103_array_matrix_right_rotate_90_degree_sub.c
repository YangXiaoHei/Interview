#include "ds.h"

void rotate_sub(int *m, int n, int ulx, int uly, int drx, int dry)
{
    int t = dry - uly;
    for (int i = 0; i < t; i++) {
        int tmp = m[ulx  * n + uly + i];
        m[ulx * n + uly + i] = m[(drx - i) * n + uly];
        m[(drx - i) * n + uly] = m[drx * n + dry - i];
        m[drx * n + dry - i] = m[(ulx + i) * n + dry];
        m[(ulx + i) * n + dry] = tmp;
    }
}

void rotate(int *m, int n)
{
    if (!m || n <= 0)
        return;

    int ulx = 0, uly = 0, drx = n - 1, dry = n - 1;
    while (ulx < drx)
        rotate_sub(m, n, ulx++, uly++, drx--, dry--);
}

int main()
{
    int n = 4;
    int *m = matrix_gen_(n, n);
    matrix_print_(m, n, n);
    rotate(m, n);
    matrix_print_(m, n, n);
}
