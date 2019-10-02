#include "ds.h"

void pre_process(int *m, int n, int *right, int *down)
{
    // 最后一列最后一行
    right[(n - 1) * n + n - 1] = m[(n - 1) * n + n - 1] == 1;
    down[(n - 1) * n + n - 1] = m[(n - 1) * n + n - 1] == 1;


    // 最后一列
    for (int i = n - 2; i >= 0; i--) {
        right[i * n + n - 1] = m[i * n + n - 1] == 1;
        down[i * n + n - 1] = m[i * n + n - 1] == 1 ? down[(i + 1) * n + n - 1] + 1 : 0;
    }

    // 最后一行
    for (int j = n - 2; j >= 0; j--) {
        right[(n - 1) * n + j] = m[(n - 1) * n + j] == 1 ? right[(n - 1) * n + j + 1] + 1 : 0;
        down[(n - 1) * n + j] = m[(n - 1) * n + j] == 1;
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            down[i * n + j] = m[i * n + j] == 1 ? down[(i + 1) * n + j] + 1 : 0;
            right[i * n + j] = m[i * n + j] == 1 ? right[i * n + j + 1] + 1 : 0;
        }
    }
}

int min(int a, int b) { return a < b ? a : b; }

void matrix_print_sub_(int *m, int r, int c, int ulx, int uly, int drx, int dry)
{
    for (int i = ulx; i <= drx; i++) {
        for (int j = uly; j <= dry; j++) 
            printf("%-3d", m[i * c + j]);
        printf("\n");
    }
    printf("\n");
}

void find_boundary_1_biggest(int *m, int n)
{
    int *right = malloc(sizeof(int) * n * n);
    int *down = malloc(sizeof(int) * n * n);
    pre_process(m, n, right, down);

    int maxa = -2147483647-1;
    int maxi = -1, maxj = -1;

    // 对于 N x N 的每个位置
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            // 对于每个边长的正方形
            int bega = min(n - i, n - j);
            for (int a = bega; a >= 1; a--) {
                int ok = right[i * n + j] >= a &&
                         right[(i + a - 1) * n + j] >= a &&
                         down[i * n + j] >= a &&
                         down[i * n + j + a - 1] >= a; 

                if (ok && a > maxa) {
                    maxi = i;
                    maxj = j;
                    maxa = a;
                }
            }
        }
    }

    int ulx = maxi, uly = maxj, drx = maxi + maxa - 1, dry = maxj + maxa - 1;
    matrix_print_sub_(m, n, n, ulx, uly, drx, dry);
}

int main()
{
    int m[] = {
        0, 1, 1, 1, 1,
        0, 1, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 1, 1, 1, 1,
        0, 1, 0, 1, 1
    };
    int n = 5;
    matrix_print_(m, n, n);
    find_boundary_1_biggest(m, n);
}
