#include "ds.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int exchange_money_no_dup(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim <= 0)
        return 0;

    int imax = 2147483647;
    int *dp = malloc(sizeof(int) * (aim + 1));
    memset(dp, 0, sizeof(int) * (aim + 1));
    for (int i = 1; i <= aim; i++)
        dp[i] = imax;

    if (money[0] <= aim)
        dp[money[0]] = 1;

    int left = 0;
    for (int i = 1; i < size; i++) {
        for (int j = aim; j >= 1; j--) {
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
    int k = randWithRange(0, 20);
    int money[] = { 5, 2, 3, 4 };
    int size = sizeof(money) / sizeof(money[0]);
    int cnt = exchange_money_no_dup(money, size, k);
    printArray(money, size);
    printf("k = %d cnt = %d\n", k, cnt);    
}
