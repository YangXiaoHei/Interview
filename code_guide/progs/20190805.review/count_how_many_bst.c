#include "ds.h"

int count_how_many_bst(int n)
{
    if (n <= 0)
        return 0;

    if (n <= 2)
        return n;

    int *dp = malloc(sizeof(int) * (n + 1));
    memset(dp, 0, sizeof(int) * (n + 1));
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++) 
        for (int j = 0; j < i; j++)
            dp[i] += dp[j] * dp[i - j - 1];

    int res = dp[n];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 20; i++)
        printf("i = %d bst count = %d\n", i, count_how_many_bst(i));
}
