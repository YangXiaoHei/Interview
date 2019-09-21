#include "ds.h"

void rotate_matrix(int *m, int n)
{
    // 沿右上角 -> 左下角对角线翻转
    for (int i = 0; i <= n - 2; i++) {
        for (int j = n - i - 2; j >= 0; j--) {
            swap(m + i * n + j, m + (n - j - 1) * n + (n - i - 1));
        }
    }

    // 上下翻转
    for (int j = 0; j <= n - 1; j++) {
        int p = 0, q = n - 1;
        while (p < q) {
            swap(m + p * n + j, m + q * n + j);
            p++, q--;
        }
    }
}

int main()
{
    int n = 4;
    int *m = matrix_gen_(n, n);
    matrix_print_(m, n, n);
    rotate_matrix(m, n);
    matrix_print_(m, n, n);
}
