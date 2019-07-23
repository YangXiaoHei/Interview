#include "ds.h"

long matrix_min_path_sum_best(long *m, int r, int c)
{
    int more = r > c ? r : c;
    int less = more == r ? c : r;
    int rowmore = more == r;
    long *dp = malloc(sizeof(long) * less);
    if (!dp) exit(1);

    for (int i = 0; i < less; i++)
        dp[i] = rowmore ? m[0 * c + i] : m[i * c + 0];

    // 如果行数过多，外层遍历行，反之外层遍历列
    for (int i = 1; i < more; i++) {
        dp[0] = rowmore ? m[i * c + 0] : m[0 * c + i];
        for (int j = 1; j < less; j++) {
            long min = dp[j] < dp[j - 1] ? dp[j] : dp[j - 1];
            dp[j] = min + (rowmore ? m[i * c + j] : m[j * c + i]); 
       }
    }
    long res = dp[less - 1];
    free(dp);
    return res;
}

long matrix_min_path_sum(long *m, int r, int c)
{
    long *dp = malloc(sizeof(long) * c);
    if (!dp) exit(1);
    memset(dp, 0, sizeof(long) * c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            long up = 0, left = 0;
            if (i > 0)
                up = dp[j];
            if (j > 0)
                left = dp[j - 1];
            dp[j] = (up < left ? up : left) + m[i * c + j];
        }
    }
    long res = dp[c - 1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    long *m = matrix_gen(4, 5);
    matrix_print(m, 4, 5);
    long sum = matrix_min_path_sum(m, 4, 5);
    long sum2 = matrix_min_path_sum_best(m, 4, 5);
    printf("min path sum %ld %ld\n", sum, sum2);
}
