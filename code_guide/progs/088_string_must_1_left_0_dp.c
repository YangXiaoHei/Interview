#include "ds.h"

long must_1_left_0(int n)
{
    if (n <= 0)
        return -1;

    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    long *dp = malloc(sizeof(long) * (n + 1));
    dp[n] = 1;
    dp[n - 1] = 2;
    for (int i = n - 2; i >= 1; i--)
        dp[i] = dp[i + 1] + dp[i + 2];

    long res = dp[1];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 100; i++)
        printf("res(%d) = %-3ld\n", i, must_1_left_0(i));
}
