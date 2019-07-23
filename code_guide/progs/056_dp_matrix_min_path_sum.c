#include "ds.h"

long matrix_min_path_sum(long *m, int r, int c)
{
    long *dp = malloc(sizeof(long) * (r * c));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(long) * (r * c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            long up = 0, left = 0;
            if (i > 0)
                up = dp[(i - 1) * c + j];
            if (j > 0)
                left = dp[i * c + j - 1];
            dp[i * c + j] = (up < left ? up : left) + m[i * c + j];
        }
    }

    // 打印出该条路径
    int i = r - 1, j = c - 1;
    while (i != 0 || j != 0) {
        printf("%ld\n", m[i * c + j]);
        int up = 2147483647, left = 2147483647;

        if (i > 0)
            up = dp[(i - 1) * c + j];

        if (j > 0)
            left = dp[i * c + j - 1];

        if (up > left)
            j--;
        else
            i--;
    }
    long res = dp[(r - 1) * c + c - 1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    long *m = matrix_gen(7, 8);
    matrix_print(m, 7, 8);
    long sum = matrix_min_path_sum(m, 7, 8);
    printf("min path sum %ld\n", sum);
}
