#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *dp = malloc(sizeof(int) * (aim + 1));
    if (!dp) exit(1);

    int imax = 2147483647;
    dp[0] = 0;
    for (int i = 1; i <= aim; i++)
        dp[i] = imax;
    dp[money[0]] = 1;

    for (int i = 1; i < size; i++) {
        for (int j = aim; j >= 0; j--) {
            int num = dp[j];
            if (j - money[i] >= 0 && dp[j - money[i]] != imax)
                num = min(num, dp[j - money[i]] + 1);
            dp[j] = num;
        }
    }
    
    int res = dp[aim];
    free(dp);
    return res == imax ? -1 : res;
}

int main(int argc, char *argv[])
{
    int money[] = { 5, 10, 1 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    int res = exchange_money(money, size, aim);
    printf("res = %d\n", res);
}
