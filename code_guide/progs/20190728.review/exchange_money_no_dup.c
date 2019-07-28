#include "ds.h"

int min(int a, int b) { return a < b ? a : b; }

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
       return 0; 

    int *dp = malloc(sizeof(int) * size * (aim + 1));
    if (!dp) exit(1);

    int imax = 2147483647;
    dp[0 * (aim + 1) + 0] = 0;
    for (int i = 1; i <= aim; i++)
        dp[0 * (aim + 1) + i] = imax;
    dp[0 * (aim + 1) + money[0]] = 1;

    for (int i = 1; i < size; i++)
        dp[i * (aim + 1) + 0] = 0;

    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            int num = imax;
            if (j - money[i] >= 0 && dp[(i - 1) * (aim + 1) + j - money[i]] != imax)
                num = dp[(i - 1) * (aim + 1) + j - money[i]] + 1;
            dp[i * (aim + 1) + j] = min(num, dp[(i - 1) * (aim + 1) + j]); 
        }
    }

    int res = dp[(size - 1) * (aim + 1) + aim];
    free(dp);
    return res == imax ? -1 : res;
}

int main(int argc, char *argv[])
{
    int money[] = { 1, 15, 20, 25, 10 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    int res = exchange_money(money, size, aim);
    printf("res = %d\n", res);
}
