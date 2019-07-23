#include "ds.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim <= 0)
        return 0;

    int imax = 2147483647;
    int *dp = malloc(sizeof(int) * (aim + 1));
    memset(dp, 0, sizeof(int) * (aim + 1));
    
    for (int j = 1; j <= aim; j++) {
        dp[j] = imax; 
        if (j - money[0] >= 0 && dp[j - money[0]] != imax)
            dp[j] = dp[j - money[0]] + 1;
    }

    int left = 0;
    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            left = imax;
            if (j - money[i] >= 0 && dp[j - money[i]] != imax)
                left = dp[j - money[i]] + 1;
            dp[j] = min(left, dp[j]);
        }
    }

    int res = dp[aim];
    free(dp);
    return res == imax ? -1 : res;
}

int main(int argc, char *argv[])
{
    int k = randWithRange(0, 30);
    printf("k = %d\n", k);
    int money[] = { 5, 2, 3 };
    printArray(money, 3);
    int cnt = exchange_money(money, 3, k);
    printf("cnt = %d\n", cnt);
}
