#include "ds.h"

void rorate_right_90(int *m, int n)
{
    if (!m || n <= 0)
        return;

    // 沿右上 -> 左下对角线翻转
    for (int i = 0; i <= n - 2; i++) {
        for (int j = n - 2 - i; j >= 0; j--) {
            swap(m + i * n + j, m + (n - 1 - j) * n + (n - 1 - i));
        }
    }

    // 上下翻转
    int ui = 0, di = n - 1;
    while (ui < di) {
        for (int j = 0; j <= n - 1; j++)
            swap(m + ui * n + j, m + di * n + j);
        ui++, di--;
    }
}

int main()
{
    int n = 5;
    int *m = matrix_gen_(n, n);
    matrix_print_(m, n, n);
    rorate_right_90(m, n);
    matrix_print_(m, n, n);
}
