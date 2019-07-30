#include "ds.h"

int exchange_money(int *money, int size, int aim)
{
    if (!money || size <= 0 || aim < 0)
        return 0;

    int *dp = malloc(sizeof(int) * (aim + 1));
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * (aim + 1));

    dp[0] = 1;
    for (int i = 1; i * money[0] <= aim; i++)
        dp[i * money[0]] = 1;

    for (int i = 1; i < size; i++) {
        for (int j = 1; j <= aim; j++) {
            if (j - money[i] >= 0)
                dp[j] += dp[j - money[i]];
        }
    }
    int res = dp[aim];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int money[] = { 1, 4, 15, 20, 10 };
    int size = sizeof(money) / sizeof(money[0]);
    printArray(money, size);
    int aim;
    scanf("%d", &aim);
    printf("res = %d\n", exchange_money(money, size, aim));
}
