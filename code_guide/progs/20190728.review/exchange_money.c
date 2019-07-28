#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }  

int exchange_money(int *money, int size, int aim)
{
    int *dp = malloc(sizeof(int) * size * (aim + 1));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * size * (aim + 1));

    dp[0 * (aim + 1) + 0] = 0;
    for (int i = 1; i < size; i++)
        dp[i * (aim + 1) + 0] = 0;

    for (int i = 1; i <= aim; i++) 
        dp[0 * (aim + 1) + i] = 2147483647;

    for (int i = 1; i * money[0] <= aim; i++)
        dp[0 * (aim + 1) + i * money[0]] = i;

    // dp[i][j] = min{ dp[i - 1][j], dp[i][j - money[i]] }
    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            int num = 2147483647;

            // 不用 i 这张就能换钱成功
            if (dp[(i - 1) * (aim + 1) + j] != 2147483647)
               num = min(dp[(i - 1) * (aim + 1) + j], num);

            // 用 k 张 money[i] , 在用 k - 1 张 money[i] 的基础上加上这一张
            if (j - money[i] >= 0 && dp[i * (aim + 1) + j - money[i]] != 2147483647)
               num = min(dp[i * (aim + 1) + j - money[i]] + 1, num);

            dp[i * (aim + 1) + j] = num;
        }
    } 

    int res = dp[(size - 1) * (aim + 1) + aim];
    free(dp);
    return res == 2147483647 ? -1 : res;
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 10, 25, 1 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim = randWithRange(1, 200);
    printf("aim = %d\n", aim);
    int res = exchange_money(money, size, aim);
    printf("%d\n", res);
}
