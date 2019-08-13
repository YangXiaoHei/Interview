#include "ds.h"

long fibonacci(int n)
{
    if (n <= 1)
        return 1;

    long *dp = malloc(sizeof(long) * n);
    dp[0] = dp[1] = 1;

    for (int i = 2; i < n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    long res = dp[n - 1]; 
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int i = 100000000;
    BENCHMARK(
                printf("fibonacci(%d) = %-3ld\n", i, fibonacci(i));
            );
}
