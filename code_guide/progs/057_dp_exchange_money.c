#include "ds.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int exchange_money(int *money, int size, int aim)
{
    int *dp = malloc(sizeof(int) * (aim + 1) * size);
    memset(dp, 0, sizeof(int) * (aim + 1) * size);

    int imax = 2147483647;
    // 设置初始状态
    for (int j = 1; j <= aim; j++) {
        dp[0 * (aim + 1) + j] = imax;
        if (j - money[0] >= 0 && dp[0 * (aim + 1) + j - money[0]] != imax)
            dp[0 * (aim + 1) + j] = dp[0 * (aim + 1) + j - money[0]] + 1;
    }

    int left;
    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            left = imax;
            if (j - money[i] >= 0 && dp[i * (aim + 1) + j - money[i]] != imax)
                left = dp[i * (aim + 1) + j - money[i]] + 1;
            dp[i * (aim + 1) + j] = min(left, dp[(i - 1) * (aim + 1) + j]); 
        }
    }

    int res = dp[(size - 1) * (aim + 1) + aim];
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
