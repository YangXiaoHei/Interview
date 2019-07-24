#include "ds.h"

int count_bst(int n)
{
    int *dp = malloc(sizeof(int) * (n + 1));
    memset(dp, 0, sizeof(int) * (n + 1));

    dp[0] = 1;

    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= i; j++) 
            dp[i] += dp[j - 1] * dp[i - j];

    int res = dp[n];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int n = randWithRange(1, 20);
    printf("n = %d bst count = %d\n", n, count_bst(n));
}
