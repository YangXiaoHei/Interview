#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int min_sum_path(int *m, int r, int c)
{
    if (!m || r <= 0 || c <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * c);
    if (!dp) exit(1);

    dp[0] = m[0 * c + 0];
    for (int i = 1; i < c; i++)
        dp[i] = dp[i - 1] + m[0 * c + i];

    for (int i = 1; i < r; i++) {
        dp[0] += m[i * c + 0];
        for (int j = 1; j < c; j++) {
           dp[j] = m[i * c + j] + min(dp[j], dp[j - 1]); 
        }
    }

    int res = dp[c - 1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int *m = matrix_gen_(4, 5);
    matrix_print_(m, 4, 5);
    printf("sum = %d\n", min_sum_path(m, 4, 5));
}
