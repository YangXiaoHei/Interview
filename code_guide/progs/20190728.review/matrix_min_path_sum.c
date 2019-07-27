#include "ds.h"

int  min(int a, int c)
{
    return a < c ? a : c;
}

int max_sum_path(int *m, int r, int c)
{
    int *dp = malloc(sizeof(int) * r * c);
    memset(dp, 0, sizeof(int) * r * c);

    dp[0 * c + 0] = m[0 * c + 0];
    for (int i = 1; i < r; i++)
        dp[i * c + 0] = m[i * c + 0] + dp[(i - 1) * c + 0];

    for (int i = 1; i < c; i++)
        dp[0 * c + i] = m[0 * c + i] + dp[0 * c + i - 1];

    for (int i = 1; i < r; i++) 
        for (int j = 1; j < c; j++) 
            dp[i * c + j] = m[i * c + j] + min(dp[(i - 1) * c + j], dp[i * c + j - 1]);

    int *path = malloc(sizeof(int) * (r + c - 1));
    memset(path, 0, sizeof(int) * (r + c - 1));
    int i = r - 1, j = c - 1;
    int idx = r + c - 2;
    while (idx >= 0) {
        int up = 2147483647; 
        int left = 2147483647; 

        if (i >= 0 && j >= 0) {
            up = dp[(i - 1) * c + j];
            left = dp[i * c + j - 1];
        } else if (j < 0 && i < 0)
            break;
        else if (j < 0)
            up = dp[(i - 1) * c + j];
        else
            left = dp[i * c + j - 1];

        path[idx--] = m[i * c + j];
        if (min(up, left) == up)
            i--;
        else
            j--;
    }

    printArray(path, r + c - 1);
    free(path);

    int res = dp[(r - 1) * c + c - 1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int *m = matrix_gen_(4, 5);
    matrix_print_(m, 4, 5);
    int sum = max_sum_path(m, 4, 5);
    printf("sum = %d\n", sum);
}
