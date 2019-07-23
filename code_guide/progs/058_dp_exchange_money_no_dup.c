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
    int *dp = malloc(sizeof(int) * size * (aim + 1));
    memset(dp, 0, sizeof(int) * size * (aim + 1));

    for (int j = 0; j <= aim; j++)
        dp[0 * (aim + 1) + j] = imax;

    if (money[0] <= aim)
        dp[money[0]] = 1;

    int left = 0;
    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            left = imax;
            if (j - money[i] >= 0 && dp[(i - 1) * (aim + 1) + j - money[i]] != imax)
                left = dp[(i - 1) * (aim + 1) + j - money[i]] + 1;
           dp[i * (aim + 1) + j] = min(left, dp[(i - 1) * (aim + 1) + j]); 
        }
    }

    int res = dp[(size - 1) * (aim + 1) + aim];
    free(dp);
    return res == imax ? -1 : res;
}

int main(int argc, char *argv[])
{
    int k = randWithRange(0, 20);
    int money[] = { 5, 2, 3, 5 };
    int size = sizeof(money) / sizeof(money[0]);
    int cnt = exchange_money_no_dup(money, size, k);
    printf("k = %d cnt = %d\n", k,  cnt);
}
