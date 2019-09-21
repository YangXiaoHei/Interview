#include "ds.h"

void rotate_sub(int *m, int n, int ulx, int uly, int drx, int dry)
{
    int times = dry - uly;
    for (int j = 0; j < times; j++) {
        int t = m[ulx * n + uly + j];
        m[ulx * n + uly + j] = m[(drx - j) * n + uly];
        m[(drx - j) * n + uly] = m[drx * n + dry - j];
        m[drx * n + dry - j] = m[(ulx + j) * n + dry];
        m[(ulx + j) * n + dry] = t;
    }
}

void rotate(int *m, int n)
{
    if (!m || n <= 0)
        return;

    int ulx = 0, uly = 0, drx = n - 1, dry = n - 1;
    while (ulx <= drx && uly <= dry) 
        rotate_sub(m, n, ulx++, uly++, drx--, dry--);
}

int main()
{
    int n = 6;
    int *m = matrix_gen_(n, n);
    matrix_print_(m, n, n);
    rotate(m, n);
    matrix_print_(m, n, n);
}
